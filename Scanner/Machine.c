/*
 * Machine.c
 *
 *  A 3D scanner controller: rotates the platform, reads IR distance,
 *  moves Z-axis layer by layer, with nonblocking scan, pause/resume,
 *  and abort.
 *
 *  Created on: May 26, 2025
 *      Author: daomi
 */

#include <Scanner/Machine.h>
#include <Scanner/StepperMotor.h>
#include <Scanner/IRSensor.h>
#include <Clock.h>
#include <AWSIoT.h>
#include <Configuration.h>
#include <stdint.h>
#include <stdbool.h>



/* Machine sub-states */
typedef enum {
    MACHINE_STATE_IDLE,      // ready for next revolution
    MACHINE_STATE_ROTATING,  // performing one revolution & taking IR readings
    MACHINE_STATE_Z_MOVE,    // moving Z up one layer
    MACHINE_STATE_PAUSED,    // paused — recovering user-moved axes
    MACHINE_STATE_HOMING     // homing procedure
} MachineState;

/* Steppers */
static StepperMotor* platform;
static StepperMotor* zAxis;

/* Calibration */
static float stepsPerRev;
static float stepsPerMM;
static float revTime;
static float zAxisSpeed;

/* Scan geometry parameters */
static float scanHeight;     // total mm to scan
static int   layersPerMM;    // layers per mm (<= MAX_LAYERS_PER_MM)
static int   scansPerLayer;  // revolutions per layer (<= MAX_SCANS_PER_LAYER)

/* Dynamic state */
static bool          scanning;
static MachineState  state;
static float         zPos;             // in mm
static float         platformAngle;    // in degrees (–180 to +180)
static int           pointsScanned;    // total points collected
static int16_t      scanResult[MAX_SCANS_PER_LAYER];

/* IR-reading buffers */
static int16_t readingsBuffer[READINGS_PER_SCAN];
static int      currentReadingIndex;
unsigned long lastIRTimeUs;

/* Pause recovery */
static float pausePlatformAngle;
static float pauseZPos;
static bool  pauseReturned;

/* Helper: median of small buffer via insertion-sort */
static int16_t computeMedian(int16_t *buf, int n) {
//    int i;
//    for (i = 1; i < n; ++i) {
//        int16_t v = buf[i];
//        int j = i - 1;
//        while (j >= 0 && buf[j] > v) {
//            buf[j+1] = buf[j];
//            --j;
//        }
//        buf[j+1] = v;
//    }
//    int16_t median;
//    if (n % 2 == 0) {
//        median = (buf[n / 2 - 1] + buf[n / 2]) / 2;
//    } else {
//        median = buf[n / 2];
//    }
//
//    return median;

    unsigned long tot = 0;
    int i;
    for (i = 0; i < n; i++) {
        tot = tot + buf[i];
    }
    return tot/n;
}

/* Clamp setters */
void Machine_setLayersPerMM(int layers) {
    if (layers < 1) layers = 1;
    if (layers > MAX_LAYERS_PER_MM) layers = MAX_LAYERS_PER_MM;
    layersPerMM = layers;
}
void Machine_setScansPerLayer(int scans) {
    if (scans < 1) scans = 1;
    if (scans > MAX_SCANS_PER_LAYER) scans = MAX_SCANS_PER_LAYER;
    scansPerLayer = scans;
}

/* Initialization */
void Machine_init() {
    IRSensor_init();
    platform = StepperMotor_new(
        PLATFORM_IN1_PORT, PLATFORM_IN1_PIN,
        PLATFORM_IN2_PORT, PLATFORM_IN2_PIN,
        PLATFORM_IN3_PORT, PLATFORM_IN3_PIN,
        PLATFORM_IN4_PORT, PLATFORM_IN4_PIN
    );
    zAxis = StepperMotor_new(
        ZAXIS_IN1_PORT, ZAXIS_IN1_PIN,
        ZAXIS_IN2_PORT, ZAXIS_IN2_PIN,
        ZAXIS_IN3_PORT, ZAXIS_IN3_PIN,
        ZAXIS_IN4_PORT, ZAXIS_IN4_PIN
    );

    /* default calibration */
    Machine_setStepsPerRev(PLATFORM_STEPS_PER_REV);
    Machine_setStepsPerMM(ZAXIS_STEPS_PER_MM);
    Machine_setPlatformRevTime(PLATFORM_MIN_REV_TIME*1);
    Machine_setZAxisSpeed(ZAXIS_MAX_SPEED);

    /* default scan geometry */
    scanHeight    = 70.0f;
    layersPerMM   = 1;
    scansPerLayer = 180;

    /* initial dynamic state */
    scanning      = false;
    state         = MACHINE_STATE_IDLE;
    zPos          = 0.0f;
    platformAngle = 0.0f;
    pointsScanned = 0;
    pauseReturned = false;


    IRSensor_readValue(); //read it to initialize
}


static inline float clamp(float n, float low, float high) {
    if (n > high) {
        return high;
    }
    if (n < low) {
        return low;
    }
    return n;
}

/* Calibration setters */
void Machine_setStepsPerRev(float steps) {
    stepsPerRev = clamp(steps, 1500, 2500);
    StepperMotor_setSpeed(platform, stepsPerRev / revTime);
}
void Machine_setStepsPerMM(float steps) {
    stepsPerMM = clamp(steps, 250, 750);
    StepperMotor_setSpeed(zAxis, stepsPerMM * zAxisSpeed);
}
void Machine_setPlatformRevTime(float time) {
    revTime = clamp(time, PLATFORM_MIN_REV_TIME, PLATFORM_MIN_REV_TIME*4);
    StepperMotor_setSpeed(platform, stepsPerRev / revTime);
}
void Machine_setZAxisSpeed(float speed) {
    zAxisSpeed = clamp(speed, ZAXIS_MAX_SPEED*0.25 , ZAXIS_MAX_SPEED);
    StepperMotor_setSpeed(zAxis, stepsPerMM * zAxisSpeed);
}

/* Geometry setters/getters */
void  Machine_setScanHeight(float height) { scanHeight = height; }
float Machine_getScanHeight(void)         { return scanHeight; }
int   Machine_getLayersPerMM(void)        { return layersPerMM; }
int   Machine_getScansPerLayer(void)      { return scansPerLayer; }

/* Control API */
void Machine_scan(void) {
    if (!scanning) {
        scanning      = true;
        state         = MACHINE_STATE_IDLE;
        pointsScanned = 0;
        pauseReturned = false;
    }
}
void Machine_pause(void) {
    if (scanning
        && state == MACHINE_STATE_IDLE
        && StepperMotor_isIdle(platform)
        && StepperMotor_isIdle(zAxis))
    {
        /* record current pose */
        pausePlatformAngle = platformAngle;
        pauseZPos          = zPos;
        pauseReturned      = false;
        state              = MACHINE_STATE_PAUSED;
    }
}
void Machine_unPause(void) {
    if (scanning && state == MACHINE_STATE_PAUSED) {
        /* resume scanning state machine */
        state         = MACHINE_STATE_IDLE;
        pauseReturned = false;
    }
}
void Machine_abort(void) {
    scanning = false;
    state    = MACHINE_STATE_IDLE;
}
bool Machine_isScanning(void) {
    return scanning
        && state != MACHINE_STATE_PAUSED
        && state != MACHINE_STATE_HOMING;
}
bool Machine_isPaused(void)   { return state == MACHINE_STATE_PAUSED; }

void Machine_home(void) {
    if (state != MACHINE_STATE_HOMING) {
        state = MACHINE_STATE_HOMING;
    }
}

/* Main step: call frequently from your main loop */
void Machine_step(void) {
    /* 1) Handle homing */
    if (state == MACHINE_STATE_HOMING) {
        /* TODO: real homing logic */
        state = MACHINE_STATE_IDLE;
        return;
    }

    /* 2) Handle pause recovery */
    if (state == MACHINE_STATE_PAUSED) {
        if (!pauseReturned
            && StepperMotor_isIdle(platform)
            && StepperMotor_isIdle(zAxis))
        {
            /* restore platform */
            float dAng  = pausePlatformAngle - platformAngle;
            float steps = dAng / 360.0f * stepsPerRev;
            StepperMotor_rotate(platform, steps);
            /* restore Z */
            float dzSteps = (pauseZPos - zPos) * stepsPerMM;
            StepperMotor_rotate(zAxis, dzSteps);
            pauseReturned = true;
        }
        /* do not advance scan while paused */
    }

    /* 3) Scanning state machine */
    else if (scanning) {
        /* compute totals */
        int totalLayers = (int)(scanHeight * layersPerMM + 1.0f);
        if (totalLayers < 1) totalLayers = 1;
        int totalPoints = totalLayers * scansPerLayer;

        switch (state) {
            case MACHINE_STATE_IDLE:

                /* start next revolution if any points remain */
                if (StepperMotor_isIdle(platform)
                    && StepperMotor_isIdle(zAxis)
                    && pointsScanned < totalPoints)
                {
                    StepperMotor_rotate(platform, -stepsPerRev/scansPerLayer);
                    currentReadingIndex = 0;
                    lastIRTimeUs        = Clock_getMicrosecond();
                    state               = MACHINE_STATE_ROTATING;


                }
                /* if all done, finish */
                else if (pointsScanned >= totalPoints) {
                    scanning = false;
                }
                break;

            case MACHINE_STATE_ROTATING: {
                unsigned long now     = Clock_getMicrosecond();
                unsigned long period  = 1000000U / IRSENSOR_RATE;
                /* sample IR at specified rate */

                if (!StepperMotor_isIdle(platform)) {
                    lastIRTimeUs = now;
                }
                if (currentReadingIndex < READINGS_PER_SCAN
                    && now - lastIRTimeUs >= period)
                {
                    int16_t r = IRSensor_readValue();
                    readingsBuffer[currentReadingIndex++] = r;

                    lastIRTimeUs = now;
                }
                /* when rotation ends, store median */
                if (currentReadingIndex == READINGS_PER_SCAN) {

                    int16_t m = computeMedian(readingsBuffer, currentReadingIndex);
                    //Report("\r\n Reading: %d", m);
                    scanResult[pointsScanned % scansPerLayer] = m;
                    pointsScanned++;
                    /* next: Z move every scansPerLayer revolutions */
                    if ((pointsScanned % scansPerLayer) == 0) {

                        int  layerIndex = pointsScanned / scansPerLayer;  // 1-based layer #
                        int  offset     = (layerIndex - 1) * scansPerLayer;
                        bool lastLayer  = (layerIndex >= totalLayers);
                        // send this layer’s full scansPerLayer readings to AWS
                        Report("\r\n Finished layer %d\r\n", layerIndex);
                        AWSIoT_sendLayerResult(layerIndex,
                                               &scanResult,
                                               scansPerLayer,
                                               zPos,
                                               lastLayer);
                        state = MACHINE_STATE_Z_MOVE;
                    } else {
                        state = MACHINE_STATE_IDLE;
                    }
                }
                break;
            }

            case MACHINE_STATE_Z_MOVE:
                /* if done, stop */
                if (pointsScanned >= totalPoints) {

                    scanning = false;
                    state    = MACHINE_STATE_IDLE;
                    break;
                }
                /* move Z up one layer */

                if (StepperMotor_isIdle(zAxis)) {

                    float stepMM = 1.0f / layersPerMM;
                    if (zPos + stepMM > ZAXIS_MAX) {
                        /* cannot exceed max */
                        scanning = false;
                        state    = MACHINE_STATE_IDLE;
                    } else {
                        Machine_moveZ(stepMM);
                        state = MACHINE_STATE_IDLE;
                    }
                }
                break;

            default:
                break;
        }
    }

    /* 4) Step motors and update dynamic pose */
    float da = StepperMotor_step(platform);
    float dz = StepperMotor_step(zAxis);
    zPos += dz / stepsPerMM;
    platformAngle += 360.0f * da / stepsPerRev;
    /* wrap angle to –180…+180 */
    if (platformAngle > 180.0f)  platformAngle -= 360.0f;
    if (platformAngle < -180.0f) platformAngle += 360.0f;
}

/* Manual moves */
void Machine_rotatePlatform(float deg) {
    StepperMotor_rotate(platform, deg / 360.0f * stepsPerRev);
}
void Machine_moveZ(float mm) {
    StepperMotor_rotate(zAxis, mm * stepsPerMM);
}

/* Getters */
float    Machine_getZPos(void)          { return zPos; }
float    Machine_getPlatformAngle(void) { return platformAngle; }
float    Machine_getStepsPerRev(void)   { return stepsPerRev; }
float    Machine_getStepsPerMM(void)    { return stepsPerMM; }
float    Machine_getPlatformRevTime(void){ return revTime; }
float    Machine_getZAxisSpeed(void)    { return zAxisSpeed; }
int      Machine_getPointsScanned(void) { return pointsScanned; }
int16_t*Machine_getScanResult(void)    { return scanResult; }

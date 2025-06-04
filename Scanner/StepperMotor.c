/*
 * StepperMotor.c
 *
 *  Created on: May 24, 2025
 *      Author: daomi
 */


#include <Scanner/StepperMotor.h>


static const int steps[8][4] = {
                         {1, 0, 0, 0},
                         {1, 1, 0, 0},
                         {0, 1, 0, 0},
                         {0, 1, 1, 0},
                         {0, 0, 1, 0},
                         {0, 0, 1, 1},
                         {0, 0, 0, 1},
                         {1, 0, 0, 1}
};

StepperMotor* StepperMotor_new(
        unsigned long   in1_port,
        unsigned int    in1_pin,
        unsigned long   in2_port,
        unsigned int    in2_pin,
        unsigned long   in3_port,
        unsigned int    in3_pin,
        unsigned long   in4_port,
        unsigned int    in4_pin
) {
    StepperMotor* stepperMotor = (StepperMotor*)malloc(sizeof(StepperMotor));

    stepperMotor->in1_port = in1_port;
    stepperMotor->in1_pin = in1_pin;
    stepperMotor->in2_port = in2_port;
    stepperMotor->in2_pin = in2_pin;
    stepperMotor->in3_port = in3_port;
    stepperMotor->in3_pin = in3_pin;
    stepperMotor->in4_port = in4_port;
    stepperMotor->in4_pin = in4_pin;

    stepperMotor->curStep = 0;
    stepperMotor->lastStep = 0;
    stepperMotor->stepsRemaining = 0;
    stepperMotor->speed = MOTOR_MAX_SPEED;

    return stepperMotor;
}

float StepperMotor_step(StepperMotor* self) {
    if ((self->stepsRemaining >= 0.5 || self->stepsRemaining <= -0.5) && (Clock_getMicrosecond() - self->lastStep > 0.5 * 1000000 / self->speed)) {

        GPIOPinWrite(self->in1_port, self->in1_pin, steps[self->curStep][0] * self->in1_pin);
        GPIOPinWrite(self->in2_port, self->in2_pin, steps[self->curStep][1] * self->in2_pin);
        GPIOPinWrite(self->in3_port, self->in3_pin, steps[self->curStep][2] * self->in3_pin);
        GPIOPinWrite(self->in4_port, self->in4_pin, steps[self->curStep][3] * self->in4_pin);

        self->lastStep = Clock_getMicrosecond();

        if (self->stepsRemaining > 0) {
            self->stepsRemaining = self->stepsRemaining-0.5;
            self->curStep = (self->curStep+1)%8;
            return 0.5;
        } else {
            self->stepsRemaining = self->stepsRemaining+0.5;
            self->curStep = self->curStep-1;
            if (self->curStep  == -1) {
                self->curStep = 7;
            }
            return -0.5;
        }
    }
    return 0;
}

void StepperMotor_rotate(StepperMotor* self, float steps) {
    self->stepsRemaining = self->stepsRemaining + steps;
}
bool StepperMotor_isIdle(StepperMotor* self) {
    return self->stepsRemaining < 0.5 && self->stepsRemaining > -0.5;
}

void StepperMotor_setSpeed(StepperMotor* self, float speed) {
    if (speed < MOTOR_MAX_SPEED) {
        self->speed = speed;
    } else {
        self->speed = MOTOR_MAX_SPEED;
    }
}



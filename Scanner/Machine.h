/*
 * Machine.h
 *
 *  Created on: May 26, 2025
 *      Author: daomi
 */

#ifndef SCANNER_MACHINE_H_
#define SCANNER_MACHINE_H_

#include <Scanner/StepperMotor.h>

void Machine_init();
void Machine_scan();
void Machine_abort();
void Machine_pause();
void Machine_unPause();
bool Machine_isScanning();
bool Machine_isPaused();
void Machine_home();
void Machine_rotatePlatform(float deg);
void Machine_moveZ(float mm);

void Machine_step();

void Machine_setStepsPerRev(float steps);
void Machine_setStepsPerMM(float steps);
void Machine_setPlatformRevTime(float time);
void Machine_setZAxisSpeed(float speed);
void Machine_setScanHeight(float height);
void Machine_setLayersPerMM(int layers);
void Machine_setScansPerLayer(int scans);

float Machine_getZPos();
float Machine_getPlatformAngle();
float Machine_getStepsPerRev();
float Machine_getStepsPerMM();
float Machine_getPlatformRevTime();
float Machine_getZAxisSpeed();
float Machine_getScanHeight();
int Machine_getLayersPerMM();
int Machine_getScansPerLayer();
int Machine_getPointsScanned();


#endif /* SCANNER_MACHINE_H_ */

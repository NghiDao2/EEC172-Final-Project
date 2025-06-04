/*
 * StepperMotor.h
 *
 *  Created on: May 24, 2025
 *      Author: daomi
 */

#ifndef SCANNER_STEPPERMOTOR_H_
#define SCANNER_STEPPERMOTOR_H_

#include <Configuration.h>
#include <stdbool.h>
#include <stdio.h>


typedef struct {

    float           stepsRemaining;
    float           speed; //steps per second
    unsigned long   lastStep;

    unsigned long   in1_port;
    unsigned int    in1_pin;
    unsigned long   in2_port;
    unsigned int    in2_pin;
    unsigned long   in3_port;
    unsigned int    in3_pin;
    unsigned long   in4_port;
    unsigned int    in4_pin;

    signed char   curStep;

} StepperMotor;



StepperMotor* StepperMotor_new(
        unsigned long   in1_port,
        unsigned int    in1_pin,
        unsigned long   in2_port,
        unsigned int    in2_pin,
        unsigned long   in3_port,
        unsigned int    in3_pin,
        unsigned long   in4_port,
        unsigned int    in4_pin
);

float StepperMotor_step(StepperMotor* self);
void StepperMotor_rotate(StepperMotor* self, float steps);
bool StepperMotor_isIdle(StepperMotor* self);
void StepperMotor_setSpeed(StepperMotor* self, float speed);



#endif /* SCANNER_STEPPERMOTOR_H_ */

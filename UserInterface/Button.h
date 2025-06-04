/*
 * Button.h
 *
 *  Created on: May 24, 2025
 *      Author: daomi
 */

#ifndef USERINTERFACE_BUTTON_H_
#define USERINTERFACE_BUTTON_H_


#include <InterruptBuffer.h>
#include <stdbool.h>
#include <stdio.h>

#define BUTTON_BUFFER_SIZE 16


typedef struct {
    unsigned long time;
    bool rise;
} ButtonInput;


DEFINE_INTERRUPT_BUFFER(ButtonInput, ButtonInputBuffer);

typedef struct {

    ButtonInputBuffer* input_buffer;

    unsigned long lastStep;

    unsigned long port;
    unsigned int pin;

    unsigned int holdDur;
    unsigned int nClicks;
    unsigned int lastClick;
    bool high;

} Button;



Button* Button_new(unsigned long port, unsigned int pin);

void Button_step(Button* self);
bool Button_isClicked(Button* self);
bool Button_isHeld(Button* self);
unsigned int Button_getClicks(Button* self);
unsigned int Button_getHoldMicrosecond(Button* self);
void Button_resetClick(Button* self);


#endif /* USERINTERFACE_BUTTON_H_ */

/*
 * Button.c
 *
 *  Created on: May 24, 2025
 *      Author: daomi
 */


#include <UserInterface/Button.h>
#include <Configuration.h>
#include <Clock.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "hw_types.h"
#include "gpio.h"


Button* Button_new(unsigned long port, unsigned int pin) {
    Button* button = (Button*)malloc(sizeof(Button));

    button->port = port;
    button->pin = pin;
    button->high = false;
    button->holdDur = 0;
    button->nClicks = 0;
    button->lastStep = 0;
    button->lastClick = 0;
    button->input_buffer = ButtonInputBuffer_new(BUTTON_BUFFER_SIZE);

    return button;
}

void Button_step(Button* self) {

    self->holdDur = 0;
    self->nClicks = 0;

    unsigned long clickTime = self->lastStep;

    while (!ButtonInputBuffer_isEmpty(self->input_buffer)) {
        ButtonInput reading = ButtonInputBuffer_pop(self->input_buffer);

        self->high = reading.rise;

        if (reading.rise) {
            if (Clock_getMicrosecond() - self->lastClick > BUTTON_CLICK_WAIT*S_TO_US) {
                self->lastClick = Clock_getMicrosecond();
                self->nClicks++;
            }
            clickTime = reading.time;
        } else {
            self->holdDur = self->holdDur + (reading.time - clickTime);
        }
    }
    if (self->high) {
        self->holdDur = self->holdDur + (Clock_getMicrosecond() - clickTime);
    }

    self->lastStep = Clock_getMicrosecond();
}

void Button_resetClick(Button* self) {
    self->nClicks = 0;
}

bool Button_isClicked(Button* self) {
    return self->nClicks > 0;
}

bool Button_isHeld(Button* self) {
    return self->high == true;
}

unsigned int Button_getClicks(Button* self) {
    return self->nClicks;
}

unsigned int Button_getHoldMicrosecond(Button* self) {
    return self->holdDur;
}



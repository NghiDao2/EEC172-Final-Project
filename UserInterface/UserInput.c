/*
 * UserInterface.cpp
 *
 *  Created on: May 24, 2025
 *      Author: daomi
 */

#include <UserInterface/UserInput.h>
#include <UserInterface/Button.h>
#include <Configuration.h>
#include <Clock.h>
#include <stdlib.h>
#include <stdio.h>

#include "hw_types.h"
#include "gpio.h"
#include "rom_map.h"



static Button* upButton;
static Button* downButton;
static Button* selectButton;


Button* UserInput_upButton() { return upButton; }
Button* UserInput_downButton() { return downButton; }
Button* UserInput_selectButton() { return selectButton; }


void processButtonInterrupt(Button* button) {
    MAP_GPIOIntClear(button->port, button->pin);

    ButtonInput reading;
    reading.time = Clock_getMicrosecond();
    reading.rise = GPIOPinRead(button->port, button->pin) == button->pin;

    ButtonInputBuffer_push(button->input_buffer, reading);
}

// Single interrupt handler for all buttons
void buttonInterruptHandler() {
    // Check upButton
    unsigned long ulStatus = MAP_GPIOIntStatus(upButton->port, true);
    if (ulStatus & upButton->pin) {
        processButtonInterrupt(upButton);
    }

    // Check downButton
    ulStatus = MAP_GPIOIntStatus(downButton->port, true);
    if (ulStatus & downButton->pin) {
        processButtonInterrupt(downButton);
    }

    // Check selectButton
    ulStatus = MAP_GPIOIntStatus(selectButton->port, true);
    if (ulStatus & selectButton->pin) {
        processButtonInterrupt(selectButton);
    }
}

void UserInput_step() {
    Button_step(upButton);
    Button_step(downButton);
    Button_step(selectButton);
}

void UserInput_init() {
    upButton = Button_new(UP_BUTTON_PORT, UP_BUTTON_PIN);
    downButton = Button_new(DOWN_BUTTON_PORT, DOWN_BUTTON_PIN);
    selectButton = Button_new(SELECT_BUTTON_PORT, SELECT_BUTTON_PIN);

    // Register the same interrupt handler for all buttons
    MAP_GPIOIntRegister(upButton->port, buttonInterruptHandler);
    MAP_GPIOIntTypeSet(upButton->port, upButton->pin, GPIO_BOTH_EDGES);
    MAP_GPIOIntClear(upButton->port, MAP_GPIOIntStatus(upButton->port, false));
    MAP_GPIOIntEnable(upButton->port, upButton->pin);

    MAP_GPIOIntRegister(downButton->port, buttonInterruptHandler);
    MAP_GPIOIntTypeSet(downButton->port, downButton->pin, GPIO_BOTH_EDGES);
    MAP_GPIOIntClear(downButton->port, MAP_GPIOIntStatus(downButton->port, false));
    MAP_GPIOIntEnable(downButton->port, downButton->pin);

    MAP_GPIOIntRegister(selectButton->port, buttonInterruptHandler);
    MAP_GPIOIntTypeSet(selectButton->port, selectButton->pin, GPIO_BOTH_EDGES);
    MAP_GPIOIntClear(selectButton->port, MAP_GPIOIntStatus(selectButton->port, false));
    MAP_GPIOIntEnable(selectButton->port, selectButton->pin);
}



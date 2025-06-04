/*
 * AdjustmentUI.c
 *
 *  Created on: May 27, 2025
 *      Author: daomi
 */


#include <UserInterface/AdjustmentUI.h>
#include <UserInterface/OLED.h>
#include <UserInterface/Button.h>
#include <UserInterface/UserInput.h>
#include <UserInterface/Utils.h>
#include <Configuration.h>
#include <Clock.h>
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>


#define TEXT_SIZE       2
#define TEXT_X          OLED_WIDTH/2
#define TEXT_Y          OLED_HEIGHT/2 - 7*TEXT_SIZE/2
#define ARROW_SIZE      2
#define LEFT_ARROW_X    0
#define RIGHT_ARROW_X   OLED_WIDTH - LEFT_ARROW_X - 6*ARROW_SIZE
#define ARROW_Y         OLED_HEIGHT/2 - 7*ARROW_SIZE/2




AdjustmentUI* AdjustmentUI_new(
        float (*getAmount)(void),
        void (*adjustAmount)(float),
        void (*onClose)(void),
        const char* unit,
        size_t decimalRound,
        bool discrete
) {

    AdjustmentUI* adjustmentUI = (AdjustmentUI*)malloc(sizeof(AdjustmentUI));

    adjustmentUI->getAmount = getAmount;
    adjustmentUI->adjustAmount = adjustAmount;
    adjustmentUI->onClose = onClose;
    adjustmentUI->unit = unit;
    adjustmentUI->decimalRound = decimalRound;
    adjustmentUI->discrete = discrete;
    adjustmentUI->opened = false;

    return adjustmentUI;
}


void AdjustmentUI_open(AdjustmentUI* self) {
    if (self->opened == false) {
        self->opened = true;

        Button_resetClick(UserInput_selectButton());
        OLED_clearScreen();
        OLED_write("<", LEFT_ARROW_X, ARROW_Y, ARROW_SIZE);
        OLED_write(">", RIGHT_ARROW_X, ARROW_Y, ARROW_SIZE);

        self->lastAmount = INFINITY;
    }
}

void AdjustmentUI_close(AdjustmentUI* self) {
    if (self->opened == true) {
        self->opened = false;
        self->onClose();
    }
}

void AdjustmentUI_step(AdjustmentUI* self) {
    if (self->opened) {

        float curAmount = RoundDecimalPlace(self->getAmount(), self->decimalRound);


        if (curAmount != self->lastAmount) {
            OLED_erase(LEFT_ARROW_X + 6*ARROW_SIZE, TEXT_Y, RIGHT_ARROW_X - LEFT_ARROW_X - 6*ARROW_SIZE, 7*TEXT_SIZE);

            char text[32];
            snprintf(text, sizeof(text), "%.*f%s", self->decimalRound, curAmount, self->unit);

            int textLength = strlen(text);
            int totalWidth = textLength * 6 * TEXT_SIZE;
            int centeredX = TEXT_X - (totalWidth / 2);
            OLED_write(text, centeredX, TEXT_Y, TEXT_SIZE);
            self->lastAmount = curAmount;
        }

        if (self->discrete) {
            if (Button_isClicked(UserInput_upButton())) {
                self->adjustAmount(1);
            }
            if (Button_isClicked(UserInput_downButton())) {
                self->adjustAmount(-1);
            }
        } else {
            float upTime = ((float) Button_getHoldMicrosecond(UserInput_upButton())) * US_TO_S;
            float dnTime = ((float) Button_getHoldMicrosecond(UserInput_downButton())) * US_TO_S;

            self->adjustAmount(upTime - dnTime);
        }

        if (Button_isClicked(UserInput_selectButton())) {
            AdjustmentUI_close(self);
        }
    }
}


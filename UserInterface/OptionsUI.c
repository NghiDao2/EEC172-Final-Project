/*
 * OptionUI.c
 *
 *  Created on: May 27, 2025
 *      Author: daomi
 */


#include <UserInterface/OptionsUI.h>
#include <UserInterface/UserInput.h>
#include <UserInterface/OLED.h>
#include <Clock.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>



#define TEXT_SEPARATION     20
#define TEXT_START_Y        8
#define TEXT_START_X        8
#define OUTLINE_SIZE_Y      TEXT_SEPARATION
#define OUTLINE_START_X     0//TEXT_START_X - 3
#define OUTLINE_SIZE_X      OLED_WIDTH// - OUTLINE_START_X * 2
#define OUTLINE_THICKNESS   2
#define TEXT_SIZE           2



unsigned long lastMoved;

OptionsUI* OptionsUI_new(const char* options[], size_t nOptions) {

    OptionsUI* optionsUI = (OptionsUI*)malloc(sizeof(OptionsUI));

    int i = 0;
    for (i = 0; i < nOptions && i < MAX_OPTIONS; i++) {
        optionsUI->options[i] = options[i];
        optionsUI->optionsVisible[i] = true;
    }

    optionsUI->opened = false;
    optionsUI->refresh = false;
    optionsUI->nOptions = nOptions;
    optionsUI->curOption = 0;
    optionsUI->curY = 0;
    optionsUI->lastY = 0;

    return optionsUI;
}

void OptionsUI_step(OptionsUI* self) {
    if (self->opened) {

        if (self->refresh) {
            OLED_clearScreen();
            int i;
            int y = 0;
            for (i = 0; i < self->nOptions; i++) {
                if (self->optionsVisible[i]) {
                    OLED_write(self->options[i], TEXT_START_X, TEXT_START_Y + y * TEXT_SEPARATION , TEXT_SIZE);

                    if (i == self->curOption) {
                        self->curY = y;
                    }
                    y++;
                }
            }
        }

        bool moved = false;


        if (Button_isClicked(UserInput_downButton())) {
            size_t start = self->curOption;
            size_t next  = start;

            // advance until we find a visible one (or loop back)
            do {
                next = (next + 1) % self->nOptions;
            } while (!self->optionsVisible[next] && next != start);

            self->curOption = next;
            moved = (next != start);
        }

        else if (Button_isClicked(UserInput_upButton())) {
            size_t start = self->curOption;
            size_t next  = start;

            // step backward until visible (or loop back)
            do {
                next = (next == 0 ? self->nOptions - 1 : next - 1);
            } while (!self->optionsVisible[next] && next != start);

            self->curOption = next;
            moved = (next != start);
        }

        if (moved) {
            int i;
            self->curY = 0;
            for (i = 0; i < self->curOption; i++) {
                if (self->optionsVisible[i]) {
                    self->curY++;
                }
            }
            lastMoved = Clock_getMicrosecond();
        }

        if (self->lastY != self->curY || self->refresh) {

            int y = TEXT_START_Y + TEXT_SEPARATION * self->curY - (OUTLINE_SIZE_Y-7*TEXT_SIZE)/2;
            int lastY = TEXT_START_Y + TEXT_SEPARATION * self->lastY - (OUTLINE_SIZE_Y-7*TEXT_SIZE)/2;

            OLED_erase( //top line
                    OUTLINE_START_X,
                    lastY,
                    OUTLINE_SIZE_X,
                    OUTLINE_THICKNESS
            );
            OLED_erase( //bottom line
                    OUTLINE_START_X,
                    lastY + OUTLINE_SIZE_Y - OUTLINE_THICKNESS,
                    OUTLINE_SIZE_X,
                    OUTLINE_THICKNESS
            );

//            OLED_erase( //left line
//                    OUTLINE_START_X,
//                    lastY,
//                    OUTLINE_THICKNESS,
//                    OUTLINE_SIZE_Y
//            );
//            OLED_erase( //right line
//                    OUTLINE_START_X + OUTLINE_SIZE_X - OUTLINE_THICKNESS,
//                    lastY,
//                    OUTLINE_THICKNESS,
//                    OUTLINE_SIZE_Y
//            );



            OLED_fillRect( //top line
                    OUTLINE_START_X,
                    y,
                    OUTLINE_SIZE_X,
                    OUTLINE_THICKNESS
            );
            OLED_fillRect( //bottom line
                    OUTLINE_START_X,
                    y + OUTLINE_SIZE_Y - OUTLINE_THICKNESS,
                    OUTLINE_SIZE_X,
                    OUTLINE_THICKNESS
            );

//            OLED_fillRect( //left line
//                    OUTLINE_START_X,
//                    y,
//                    OUTLINE_THICKNESS,
//                    OUTLINE_SIZE_Y
//            );
//            OLED_fillRect( //right line
//                    OUTLINE_START_X + OUTLINE_SIZE_X - OUTLINE_THICKNESS,
//                    y,
//                    OUTLINE_THICKNESS,
//                    OUTLINE_SIZE_Y
//            );

            self->lastY = self->curY;
        }

        self->refresh = false;
    }
}

void OptionsUI_refresh(OptionsUI* self) {
    self->refresh = true;
}

void OptionsUI_open(OptionsUI* self) {
    if (!self->opened) {
        self->opened = true;
        Button_resetClick(UserInput_selectButton());
        OptionsUI_refresh(self);
        //self->curOption = 0;
        //self->curY = 0;
        self->lastY = -1; //just to get it to redraw, so set it not equal curY
    }
}

void OptionsUI_reset(OptionsUI* self) {
    self->curOption = 0;
    self->curY = 0;
    self->lastY = -1;
}

void OptionsUI_close(OptionsUI* self) {
    if (self->opened) {
        self->opened = false;
    }
}

void OptionsUI_showOption(OptionsUI* self, size_t i) {
    if (!self->optionsVisible[i]) {
        self->optionsVisible[i] = true;
        if (self->opened) {
            OptionsUI_refresh(self);
        }
    }
}
void OptionsUI_hideOption(OptionsUI* self, size_t i) {
    if (self->optionsVisible[i]) {
        self->optionsVisible[i] = false;
        if (self->opened) {
            OptionsUI_refresh(self);
        }
    }
}

int OptionsUI_getSelected(OptionsUI* self) {
    if (self->opened && Button_isClicked(UserInput_selectButton())) {
        return self->curOption;
    }
    return -1;
}


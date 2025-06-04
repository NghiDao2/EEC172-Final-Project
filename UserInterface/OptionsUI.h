/*
 * OptionScreen.h
 *
 *  Created on: May 26, 2025
 *      Author: daomi
 */

#ifndef USERINTERFACE_OPTIONSUI_H_
#define USERINTERFACE_OPTIONSUI_H_


#include <Configuration.h>
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>


#define MAX_OPTIONS         10

typedef struct {

    const char* options[MAX_OPTIONS];
    bool optionsVisible[MAX_OPTIONS];
    size_t nOptions;
    size_t curOption;
    size_t curY;
    size_t lastY;
    bool opened;
    bool refresh;


} OptionsUI;


OptionsUI* OptionsUI_new(const char* options[], size_t nOptions);
void OptionsUI_open(OptionsUI* self);
void OptionsUI_close(OptionsUI* self);
void OptionsUI_step(OptionsUI* self);
void OptionsUI_reset(OptionsUI* self);
void OptionsUI_showOption(OptionsUI* self, size_t i);
void OptionsUI_hideOption(OptionsUI* self, size_t i);
int OptionsUI_getSelected(OptionsUI* self);




#endif /* USERINTERFACE_OPTIONSUI_H_ */

/*
 * AdjustmentUI.h
 *
 *  Created on: May 27, 2025
 *      Author: daomi
 */

#ifndef USERINTERFACE_ADJUSTMENTUI_H_
#define USERINTERFACE_ADJUSTMENTUI_H_

#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {

    const char* unit;
    float lastAmount;
    float (*getAmount)(void);
    void (*adjustAmount)(float);
    void (*onClose)(void);
    size_t decimalRound;
    bool discrete;
    bool opened;


} AdjustmentUI;


AdjustmentUI* AdjustmentUI_new(
        float (*getAmount)(void),
        void (*adjustAmount)(float),
        void (*onClose)(void),
        const char* unit,
        size_t decimalRound,
        bool discrete
);
void AdjustmentUI_open(AdjustmentUI* self);
void AdjustmentUI_close(AdjustmentUI* self);
void AdjustmentUI_step(AdjustmentUI* self);


#endif /* USERINTERFACE_ADJUSTMENTUI_H_ */

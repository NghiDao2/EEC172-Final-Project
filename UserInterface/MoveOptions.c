/*
 * MoveOptions.c
 *
 *  Created on: May 27, 2025
 *      Author: daomi
 */


#include <UserInterface/MoveOptions.h>
#include <UserInterface/OptionsUI.h>
#include <UserInterface/MainOptions.h>
#include <UserInterface/MainScreen.h>
#include <UserInterface/AdjustmentUI.h>
#include <Scanner/Machine.h>
#include <Clock.h>

#define N_OPTIONS   4

#define BACK        0
#define ZAXIS       1
#define PLATFORM    2
#define AUTO_HOME   3


#define BACK_TEXT        "Back"
#define ZAXIS_TEXT       "Z-Axis"
#define PLATFORM_TEXT    "Platform"
#define AUTO_HOME_TEXT   "Auto-home"

static const char* optionTexts[N_OPTIONS];

static bool opened;
static OptionsUI* options;
static AdjustmentUI* zAxisAdjustment;
static AdjustmentUI* platformAdjustment;


void MoveOptions_adjustZ(float dur) {
    Machine_moveZ(dur * Machine_getZAxisSpeed() * 0.9);
}
void MoveOptions_adjustPlatform(float dur) {
    Machine_rotatePlatform(dur * 360/Machine_getPlatformRevTime() * 0.9);
}

void MoveOptions_init() {
    optionTexts[BACK]           = BACK_TEXT;
    optionTexts[ZAXIS]          = ZAXIS_TEXT;
    optionTexts[PLATFORM]       = PLATFORM_TEXT;
    optionTexts[AUTO_HOME]      = AUTO_HOME_TEXT;

    options = OptionsUI_new(optionTexts, N_OPTIONS);

    zAxisAdjustment = AdjustmentUI_new(
            Machine_getZPos,
            MoveOptions_adjustZ,
            MoveOptions_open,
            "mm",
            1,
            false
    );

    platformAdjustment = AdjustmentUI_new(
            Machine_getPlatformAngle,
            MoveOptions_adjustPlatform,
            MoveOptions_open,
            "deg",
            0,
            false
    );

    opened = false;
}

void MoveOptions_open() {
    if (!opened) {
        opened = true;
        OptionsUI_open(options);
    }
}

void MoveOptions_close() {
    if (opened) {
        OptionsUI_close(options);
        opened = false;
    }
}

void MoveOptions_step() {
    if (opened) {
        switch (OptionsUI_getSelected(options)) {
            case BACK:
                MoveOptions_close();
                MainOptions_open();
                break;
            case ZAXIS:
                MoveOptions_close();
                AdjustmentUI_open(zAxisAdjustment);
                break;
            case PLATFORM:
                MoveOptions_close();
                AdjustmentUI_open(platformAdjustment);
                break;
            case AUTO_HOME:
                Machine_home();
                MoveOptions_close();
                MainScreen_open();
                break;
            default:
                break;
        }
    }

    OptionsUI_step(options);
    AdjustmentUI_step(zAxisAdjustment);
    AdjustmentUI_step(platformAdjustment);
}




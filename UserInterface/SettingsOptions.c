/*
 * SettingsOptions.c
 *
 *  Created on: May 28, 2025
 *      Author: daomi
 */

#include <UserInterface/SettingsOptions.h>
#include <UserInterface/OptionsUI.h>
#include <UserInterface/MoveOptions.h>
#include <UserInterface/AdjustmentUI.h>
#include <Scanner/Machine.h>
#include <Clock.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


#define N_OPTIONS           6

#define BACK                0
#define SCAN_HEIGHT         1
#define Z_SPEED             2
#define PLATFORM_TIME       3
#define Z_STEPS             4
#define PLATFORM_STEPS      5

#define BACK_TEXT           "Back"
#define SCAN_HEIGHT_TEXT    "Scan mm"
#define Z_SPEED_TEXT        "mm/s"
#define PLATFORM_TIME_TEXT  "s/rev"
#define Z_STEPS_TEXT        "steps/mm"
#define PLATFORM_STEPS_TEXT "steps/rev"


static const char* optionTexts[N_OPTIONS];

static bool opened;
static OptionsUI* options;
static AdjustmentUI* scanHeight;
static AdjustmentUI* zSpeed;
static AdjustmentUI* platformTime;
static AdjustmentUI* zStepsPerMM;
static AdjustmentUI* platformStepsPerRev;



void SettingsOption_adjustScanHeight(float dur) {
    Machine_setScanHeight(Machine_getScanHeight() + dur);
}

void SettingsOptions_adjustZSpeed(float dur) {
    Machine_setZAxisSpeed(dur * 0.2 + Machine_getZAxisSpeed());
}
void SettingsOptions_adjustPlatformTime(float dur) {
    Machine_setPlatformRevTime(dur + Machine_getPlatformRevTime());
}

void SettingsOptions_adjustZSteps(float dur) {
    Machine_setStepsPerMM(dur + Machine_getStepsPerMM());
}
void SettingsOptions_adjustPlatformSteps(float dur) {
    Machine_setStepsPerRev(dur + Machine_getStepsPerRev());
}

void SettingsOptions_init() {
    optionTexts[BACK]               = BACK_TEXT;
    optionTexts[SCAN_HEIGHT]        = SCAN_HEIGHT_TEXT;
    optionTexts[Z_SPEED]            = Z_SPEED_TEXT;
    optionTexts[PLATFORM_TIME]      = PLATFORM_TIME_TEXT;
    optionTexts[Z_STEPS]            = Z_STEPS_TEXT;
    optionTexts[PLATFORM_STEPS]     = PLATFORM_STEPS_TEXT;

    options = OptionsUI_new(optionTexts, N_OPTIONS);


    scanHeight = AdjustmentUI_new(
            Machine_getScanHeight,
            SettingsOption_adjustScanHeight,
            SettingsOptions_open,
            "mm",
            0,
            true
    );

    zSpeed = AdjustmentUI_new(
            Machine_getZAxisSpeed,
            SettingsOptions_adjustZSpeed,
            SettingsOptions_open,
            "mm/s",
            1,
            false
    );

    zStepsPerMM = AdjustmentUI_new(
            Machine_getStepsPerMM,
            SettingsOptions_adjustZSteps,
            SettingsOptions_open,
            "",
            1,
            true
    );

    platformTime = AdjustmentUI_new(
            Machine_getPlatformRevTime,
            SettingsOptions_adjustPlatformTime,
            SettingsOptions_open,
            "",
            1,
            false
    );

    platformStepsPerRev = AdjustmentUI_new(
            Machine_getStepsPerRev,
            SettingsOptions_adjustPlatformSteps,
            SettingsOptions_open,
            "",
            1,
            true
    );

    opened = false;
}

void SettingsOptions_open() {
    if (!opened) {
        opened = true;
        OptionsUI_open(options);
    }
}

void SettingsOptions_close() {
    if (opened) {
        OptionsUI_close(options);
        opened = false;
    }
}

void SettingsOptions_step() {
    if (opened) {
        switch (OptionsUI_getSelected(options)) {
            case BACK:
                SettingsOptions_close();
                MainOptions_open();
                break;
            case SCAN_HEIGHT:
                SettingsOptions_close();
                AdjustmentUI_open(scanHeight);
                break;
            case Z_SPEED:
                SettingsOptions_close();
                AdjustmentUI_open(zSpeed);
                break;
            case PLATFORM_TIME:
                SettingsOptions_close();
                AdjustmentUI_open(platformTime);
                break;
            case Z_STEPS:
                SettingsOptions_close();
                AdjustmentUI_open(zStepsPerMM);
                break;
            case PLATFORM_STEPS:
                SettingsOptions_close();
                AdjustmentUI_open(platformStepsPerRev);
                break;
            default:
                break;
        }
    }

    OptionsUI_step(options);
    AdjustmentUI_step(scanHeight);
    AdjustmentUI_step(zSpeed);
    AdjustmentUI_step(platformTime);
    AdjustmentUI_step(zStepsPerMM);
    AdjustmentUI_step(platformStepsPerRev);
}




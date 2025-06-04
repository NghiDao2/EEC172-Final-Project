/*
 * MainOptions.c
 *
 *  Created on: May 27, 2025
 *      Author: daomi
 */


#include <UserInterface/OptionsUI.h>
#include <UserInterface/MainScreen.h>
#include <UserInterface/MoveOptions.h>
#include <UserInterface/SettingsOptions.h>
#include <Scanner/Machine.h>
#include <Clock.h>

#define N_OPTIONS   7

#define BACK        0
#define SCAN        1
#define MOVE        2
#define SETTINGS    3
#define PAUSE       4
#define RESUME      5
#define ABORT       6


#define BACK_TEXT        "Back"
#define SCAN_TEXT        "Scan"
#define MOVE_TEXT        "Move"
#define SETTINGS_TEXT    "Settings"
#define PAUSE_TEXT       "Pause"
#define RESUME_TEXT      "Resume"
#define ABORT_TEXT       "Abort"

static const char* optionTexts[N_OPTIONS];

static bool opened;
static OptionsUI* options;

void MainOptions_init() {
    optionTexts[BACK]       = BACK_TEXT;
    optionTexts[SCAN]       = SCAN_TEXT;
    optionTexts[MOVE]       = MOVE_TEXT;
    optionTexts[SETTINGS]   = SETTINGS_TEXT;
    optionTexts[PAUSE]      = PAUSE_TEXT;
    optionTexts[RESUME]     = RESUME_TEXT;
    optionTexts[ABORT]      = ABORT_TEXT;

    options = OptionsUI_new(optionTexts, N_OPTIONS);

    opened = false;
}

void MainOptions_open() {
    if (!opened) {
        opened = true;
        OptionsUI_open(options);
    }
}

void MainOptions_close() {
    if (opened) {
        OptionsUI_close(options);
        opened = false;
    }
}

void MainOptions_step() {
    if (opened) {
        switch (OptionsUI_getSelected(options)) {

            case BACK:
                MainOptions_close();
                MainScreen_open();
                OptionsUI_reset(options);
                break;

            case SCAN:
                Machine_scan();
                MainOptions_close();
                MainScreen_open();
                OptionsUI_reset(options);
                break;

            case MOVE:
                MainOptions_close();
                MoveOptions_open();
                break;

            case SETTINGS:
                MainOptions_close();
                SettingsOptions_open();
                break;

            case PAUSE:
                Machine_pause();
                MainOptions_close();
                MainScreen_open();
                OptionsUI_reset(options);
                break;

            case RESUME:
                Machine_unPause();
                MainOptions_close();
                MainScreen_open();
                OptionsUI_reset(options);
                break;

            case ABORT:
                Machine_abort();
                MainOptions_close();
                MainScreen_open();
                OptionsUI_reset(options);
                break;

            default:
                break;
        }

        if (Machine_isScanning()) {
            OptionsUI_hideOption(options, SCAN);
            OptionsUI_hideOption(options, SETTINGS);
            OptionsUI_hideOption(options, MOVE);
            OptionsUI_hideOption(options, RESUME);
            OptionsUI_showOption(options, PAUSE);
            OptionsUI_showOption(options, ABORT);
        } else if (Machine_isPaused()) {
            OptionsUI_hideOption(options, SCAN);
            OptionsUI_hideOption(options, SETTINGS);
            OptionsUI_hideOption(options, MOVE);
            OptionsUI_showOption(options, RESUME);
            OptionsUI_hideOption(options, PAUSE);
            OptionsUI_hideOption(options, ABORT);
        } else {
            OptionsUI_showOption(options, SCAN);
            OptionsUI_showOption(options, SETTINGS);
            OptionsUI_showOption(options, MOVE);
            OptionsUI_hideOption(options, RESUME);
            OptionsUI_hideOption(options, PAUSE);
            OptionsUI_hideOption(options, ABORT);
        }
    }

    OptionsUI_step(options);
}



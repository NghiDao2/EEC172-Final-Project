/*
 * MainScreen.c
 *
 *  Created on: May 26, 2025
 *      Author: daomi
 */


#include <UserInterface/MainScreen.h>
#include <UserInterface/MainOptions.h>
#include <UserInterface/Utils.h>
#include <UserInterface/OLED.h>
#include <Scanner/Machine.h>
#include <Clock.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>




#define SCREEN_HEADER           "3D Scanner"
#define TEXT_SIZE               2
#define STATE_TEXT_X            8
#define STATE_TEXT_Y            25
#define PROGRESS_BAR_WIDTH      OLED_WIDTH - 14
#define PROGRESS_BAR_HEIGHT     17
#define PROGRESS_BAR_X          10
#define PROGRESS_BAR_Y          STATE_TEXT_Y + TEXT_SIZE*7 + 6
#define PROGRESS_BAR_THICKNESS  2
#define POSITION_TEXT_X         STATE_TEXT_X//OLED_WIDTH/2 - 32
#define POSITION_TEXT_Y         PROGRESS_BAR_Y + PROGRESS_BAR_HEIGHT + 16
#define SCAN_HEIGHT_TEXT_X      STATE_TEXT_X
#define SCAN_HEIGHT_TEXT_Y      POSITION_TEXT_X + TEXT_SIZE*7




static bool opened;
static char* lastStateText;
static float lastProgress;
static float lastZPos;


const char* getStateText() {
    if (Machine_isScanning()) {
        if (Machine_isPaused()) {
            return "Paused";
        }
        return "Scan";
    }
    return "Idle";
}

void MainScreen_init() {
    opened = false;
    MainScreen_open();
}



void MainScreen_open() {
    if (opened == false) {
        opened = true;

        Button_resetClick(UserInput_selectButton());
        OLED_clearScreen();
//        OLED_write(SCREEN_HEADER, 8, 8, 2);
//        OLED_fillRect(OLED_WIDTH * 0.2, 27, OLED_WIDTH*0.6, 2);

        //progress bar

        OLED_fillRect(PROGRESS_BAR_X, PROGRESS_BAR_Y, PROGRESS_BAR_WIDTH, PROGRESS_BAR_THICKNESS);
        OLED_fillRect(PROGRESS_BAR_X, PROGRESS_BAR_Y, PROGRESS_BAR_THICKNESS, PROGRESS_BAR_HEIGHT);
        OLED_fillRect(PROGRESS_BAR_X, PROGRESS_BAR_Y + PROGRESS_BAR_HEIGHT - PROGRESS_BAR_THICKNESS, PROGRESS_BAR_WIDTH, PROGRESS_BAR_THICKNESS);
        OLED_fillRect(PROGRESS_BAR_X + PROGRESS_BAR_WIDTH - PROGRESS_BAR_THICKNESS, PROGRESS_BAR_Y, PROGRESS_BAR_THICKNESS, PROGRESS_BAR_HEIGHT);

        lastStateText = NULL;
        lastProgress = -1;
        lastZPos = -1;
    }
}

void MainScreen_close() {
    if (opened) {
        opened = false;
    }
}

float getScanProgress() {
    return Machine_getPointsScanned() / (Machine_getScansPerLayer() * (Machine_getLayersPerMM() * Machine_getScanHeight() + 1));
}

void MainScreen_step() {

    if (opened) {
        const char* stateText = getStateText();
        if (lastStateText != stateText) {
            OLED_erase(0, STATE_TEXT_Y, OLED_WIDTH*0.5, 7*TEXT_SIZE);
            OLED_write(stateText, STATE_TEXT_X, STATE_TEXT_Y, TEXT_SIZE);
            lastStateText = stateText;
        }


        float currentProgress = RoundDecimalPlace(getScanProgress(), 2); //round to nearest percent

        if (lastProgress != currentProgress) {
            OLED_erase(OLED_WIDTH/2, STATE_TEXT_Y, OLED_WIDTH/2, 7*TEXT_SIZE);

            char progressText[5];
            snprintf(progressText, sizeof(progressText), "%d%%", (int)(currentProgress * 100));

            int textLength = strlen(progressText);
            int xPos = OLED_WIDTH - (textLength * 6*TEXT_SIZE) - STATE_TEXT_X/2;

            OLED_write(progressText, xPos, STATE_TEXT_Y, TEXT_SIZE);
            lastProgress = currentProgress;

            OLED_erase(
                    PROGRESS_BAR_X + PROGRESS_BAR_THICKNESS,
                    PROGRESS_BAR_Y + PROGRESS_BAR_THICKNESS,
                    PROGRESS_BAR_WIDTH - PROGRESS_BAR_THICKNESS*2,
                    PROGRESS_BAR_HEIGHT - PROGRESS_BAR_THICKNESS*2);

            OLED_fillRect(
                    PROGRESS_BAR_X + PROGRESS_BAR_THICKNESS,
                    PROGRESS_BAR_Y + PROGRESS_BAR_THICKNESS,
                    (PROGRESS_BAR_WIDTH - PROGRESS_BAR_THICKNESS*2) * currentProgress,
                    PROGRESS_BAR_HEIGHT - PROGRESS_BAR_THICKNESS*2);
        }


        float currentZ = RoundDecimalPlace(Machine_getZPos(), 1); //round to nearest 0.1mm

        if (lastZPos != currentZ) {
            OLED_erase(POSITION_TEXT_X, POSITION_TEXT_Y, OLED_WIDTH - POSITION_TEXT_X, 7*TEXT_SIZE);

            char zText[10];
            snprintf(zText, sizeof(zText), "Z: %.1f", currentZ);

            OLED_write(zText, POSITION_TEXT_X, POSITION_TEXT_Y, TEXT_SIZE);
            lastZPos = currentZ;
        }


        if (Button_isClicked(UserInput_selectButton())) {
            MainScreen_close();
            MainOptions_open();
        }
    }

}




/*
 * UI.h
 *
 *  Created on: May 26, 2025
 *      Author: daomi
 */

#ifndef USERINTERFACE_UI_H_
#define USERINTERFACE_UI_H_

#include <UserInterface/OLED.h>
#include <UserInterface/UserInput.h>
#include <UserInterface/MainScreen.h>
#include <UserInterface/MainOptions.h>
#include <UserInterface/MoveOptions.h>
#include <UserInterface/SettingsOptions.h>

void UI_init() {
    OLED_init();
    UserInput_init();
    MainScreen_init();
    MainOptions_init();
    MoveOptions_init();
    SettingsOptions_init();
}

void UI_step() {
    UserInput_step();
    MainScreen_step();
    MainOptions_step();
    MoveOptions_step();
    SettingsOptions_step();
}


#endif /* USERINTERFACE_UI_H_ */

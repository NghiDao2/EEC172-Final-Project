/*
 * UserInterface.h
 *
 *  Created on: May 24, 2025
 *      Author: daomi
 */

#ifndef USERINTERFACE_USERINPUT_H_
#define USERINTERFACE_USERINPUT_H_


#include <UserInterface/Button.h>
#include <Configuration.h>

#include <stdlib.h>
#include <stdio.h>


Button* UserInput_upButton();
Button* UserInput_downButton();
Button* UserInput_selectButton();

void UserInput_init();
void UserInput_step();

#endif

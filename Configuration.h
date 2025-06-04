/*
 * Configuration.h
 *
 *  Created on: May 24, 2025
 *      Author: daomi
 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include "hw_memmap.h"


//-----INPUT-------

#define UP_BUTTON_PORT          GPIOA2_BASE
#define UP_BUTTON_PIN           0x40

#define DOWN_BUTTON_PORT        GPIOA3_BASE
#define DOWN_BUTTON_PIN         0x10

#define SELECT_BUTTON_PORT      GPIOA3_BASE
#define SELECT_BUTTON_PIN       0x80

#define BUTTON_CLICK_WAIT       0.2



//-----MACHINE-------

#define MOTOR_MAX_SPEED         1024

#define PLATFORM_IN1_PORT       GPIOA0_BASE
#define PLATFORM_IN1_PIN        0x10
#define PLATFORM_IN2_PORT       GPIOA0_BASE
#define PLATFORM_IN2_PIN        0x8
#define PLATFORM_IN3_PORT       GPIOA1_BASE
#define PLATFORM_IN3_PIN        0x20
#define PLATFORM_IN4_PORT       GPIOA0_BASE
#define PLATFORM_IN4_PIN        0x20

#define ZAXIS_IN1_PORT          GPIOA0_BASE
#define ZAXIS_IN1_PIN           0x1
#define ZAXIS_IN2_PORT          GPIOA1_BASE
#define ZAXIS_IN2_PIN           0x2
#define ZAXIS_IN3_PORT          GPIOA3_BASE
#define ZAXIS_IN3_PIN           0x40
#define ZAXIS_IN4_PORT          GPIOA1_BASE
#define ZAXIS_IN4_PIN           0x1


#define PLATFORM_STEPS_PER_REV  2048
#define PLATFORM_MIN_REV_TIME   3

#define ZAXIS_STEPS_PER_MM      512
#define ZAXIS_MAX_SPEED         1

#define ZAXIS_MAX               100


#define MAX_LAYERS_PER_MM       10
#define MAX_SCANS_PER_LAYER     512
#define READINGS_PER_SCAN       1
#define IRSENSOR_RATE           8


//-----OLED-------

#define SPI_IF_BIT_RATE         10000000

#define OLED_RESET_PORT         GPIOA1_BASE
#define OLED_RESET_PIN          0x10
#define OLED_DC_PORT            GPIOA0_BASE
#define OLED_DC_PIN             0x80

#define OLED_BACKGROUND_COLOR   0x000000
#define OLED_TEXT_COLOR         0xFFFFFF

#define OLED_WIDTH              128
#define OLED_HEIGHT             128



#endif /* CONFIGURATION_H_ */

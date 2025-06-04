/*
 * OLED.c
 *
 *  Created on: May 26, 2025
 *      Author: daomi
 */

#include <UserInterface/OLED.h>

void OLED_init() {
    MAP_SPIConfigSetExpClk(GSPI_BASE,MAP_PRCMPeripheralClockGet(PRCM_GSPI),
                     SPI_IF_BIT_RATE,SPI_MODE_MASTER,SPI_SUB_MODE_0,
                     (SPI_SW_CTRL_CS |
                     SPI_4PIN_MODE |
                     SPI_TURBO_OFF |
                     SPI_CS_ACTIVELOW |
                     SPI_WL_8));
    MAP_SPIEnable(GSPI_BASE);
    Adafruit_Init();
}

void OLED_clearScreen() {
    fillScreen(OLED_BACKGROUND_COLOR);
}

void OLED_erase(int x, int y, int width, int height) {
    fillRect(x, y, width, height, OLED_BACKGROUND_COLOR);
}

void OLED_fillRect(int x, int y, int width, int height) {
    fillRect(x, y, width, height, OLED_TEXT_COLOR);
}

void OLED_write(char* string, int x, int y, int size) {
    int i;
    for (i = 0; string[i] != '\0'; i++) {
        drawChar(x + i*6*size, y, string[i], OLED_TEXT_COLOR, OLED_BACKGROUND_COLOR, size);
    }
}




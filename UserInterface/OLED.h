/*
 * OLED.h
 *
 *  Created on: May 26, 2025
 *      Author: daomi
 */

#ifndef SCANNER_OLED_H_
#define SCANNER_OLED_H_


#include "hw_types.h"
#include "hw_ints.h"
#include "hw_memmap.h"
#include "hw_common_reg.h"
#include "rom.h"
#include "rom_map.h"
#include "spi.h"
#include "prcm.h"

#include "Adafruit_SSD1351.h"
#include <Configuration.h>

void OLED_init();
void OLED_clearScreen();
void OLED_write(char* string, int x, int y, int size);
void OLED_erase(int x, int y, int width, int height);
void OLED_fillRect(int x, int y, int width, int height);


#endif /* SCANNER_OLED_H_ */

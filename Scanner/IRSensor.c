/*
 * IRSensor.c
 *
 *  Created on: May 26, 2025
 *      Author: daomi
 */


#include <Scanner/IRSensor.h>
#include <Clock.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "rom_map.h"
#include "hw_types.h"
#include "hw_i2c.h"
#include "timer_if.h"

#define I2C_ADDRESS 0x48

#define READING_DELAY MILLISECONDS_TO_TICKS(3) / 3



static int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}


int16_t IRSensor_readValue() {
    //MAP_UtilsDelay(READING_DELAY);
    const unsigned char setup[3] = {0b00000001, 0b01000010, 0b00000010};
    const unsigned char add = 0b00000000;
    unsigned char buffer[2];


    I2C_IF_Write(I2C_ADDRESS, setup, 3,0);


    I2C_IF_Write(I2C_ADDRESS, &add, 1,0);
    I2C_IF_Read(I2C_ADDRESS, buffer, 2);

    int16_t result = (buffer[0] << 8) | buffer[1];

    return result;
}

void IRSensor_init() {
}

//uint16_t IRSensor_readMedianValue(size_t count) {
//        int readings[count];
//        int i;
//
//        for (i = 0; i < count; i++) {
//            readings[i] = IRSensor_readValue();
//            MAP_UtilsDelay(READING_DELAY);
//        }
//
//        qsort(readings, count, sizeof(int), compare);
//
//        int median;
//        if (count % 2 == 0) {
//            median = (readings[count / 2 - 1] + readings[count / 2]) / 2;
//        } else {
//            median = readings[count / 2];
//        }
//
//        return median;
//}


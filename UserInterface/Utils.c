/*
 * Utils.c
 *
 *  Created on: May 27, 2025
 *      Author: daomi
 */


#include <UserInterface/Utils.h>

#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>


float RoundDecimalPlace(float number, size_t decimalPlace) {
    return roundf(number * powf(10.0f, decimalPlace)) / powf(10.0f, decimalPlace);
}

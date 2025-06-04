/*
 * Timer.h
 *
 *  Created on: May 25, 2025
 *      Author: daomi
 */

#ifndef CLOCK_H_
#define CLOCK_H_


#include "hw_types.h"
#include "hw_ints.h"
#include "hw_memmap.h"
#include "hw_common_reg.h"
#include "prcm.h"
#include "timer.h"
#include "gpio.h"


#define TICK_TIME   50
#define S_TO_US     1000000
#define US_TO_S     1/1000000

static volatile unsigned long g_ulSysTickValue;
static volatile unsigned long g_ulBase;
static volatile unsigned long g_ulRefBase;
static volatile unsigned long g_ulRefTimerInts = 0;
static volatile unsigned long g_ulIntClearVector;
unsigned long g_ulTimerInts;


void Clock_IR();
void Clock_init();
unsigned long Clock_getMicrosecond();


#endif /* CLOCK_H_ */

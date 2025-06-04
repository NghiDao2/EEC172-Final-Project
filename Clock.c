/*
 * Clock.c
 *
 *  Created on: May 27, 2025
 *      Author: daomi
 */


#include <Clock.h>


void Clock_IR(void) {
    Timer_IF_InterruptClear(g_ulRefBase);
    g_ulRefTimerInts += TICK_TIME;
}

unsigned long Clock_getMicrosecond() {
    return g_ulRefTimerInts;
}

void Clock_init() {
    g_ulRefBase = TIMERA1_BASE;
    Timer_IF_Init(PRCM_TIMERA1, g_ulRefBase, TIMER_CFG_PERIODIC, TIMER_A, 0);
    Timer_IF_IntSetup(g_ulRefBase, TIMER_A, Clock_IR);
    Timer_IF_Start(g_ulRefBase, TIMER_A, TICK_TIME);
}



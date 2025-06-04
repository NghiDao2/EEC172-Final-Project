
// Standard includes
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

// Driverlib includes
#include "hw_types.h"
#include "hw_ints.h"
#include "hw_memmap.h"
#include "hw_common_reg.h"
#include "rom.h"
#include "rom_map.h"
#include "interrupt.h"
#include "prcm.h"
#include "utils.h"
#include "uart.h"

// Common interface includes
#include "uart_if.h"
#include "i2c_if.h"
#include "spi.h"
#include "timer_if.h"
#include "pin_mux_config.h"
#include "Adafruit_SSD1351.h"


#include <AWSIoT.h>
#include <Clock.h>
#include <UserInterface/UI.h>
#include <Scanner/Machine.h>


//*****************************************************************************
//                      MACRO DEFINITIONS
//*****************************************************************************
#define APPLICATION_VERSION     "1.4.0"
#define APP_NAME                "I2C Demo"
#define UART_PRINT              Report
#define FOREVER                 1
#define CONSOLE                 UARTA0_BASE
#define FAILURE                 -1
#define SUCCESS                 0
#define RETERR_IF_TRUE(condition) {if(condition) return FAILURE;}
#define RET_IF_ERR(Func)          {int iRetVal = (Func); \
                                   if (SUCCESS != iRetVal) \
                                     return  iRetVal;}

//*****************************************************************************
//                 GLOBAL VARIABLES -- Start
//*****************************************************************************
#if defined(ccs)
extern void (* const g_pfnVectors[])(void);
#endif
#if defined(ewarm)
extern uVectorEntry __vector_table;
#endif
//*****************************************************************************
//                 GLOBAL VARIABLES -- End
//*****************************************************************************


//****************************************************************************
//                      LOCAL FUNCTION DEFINITIONS
//****************************************************************************

#define FOREVER 1



//*****************************************************************************
//
//! Board Initialization & Configuration
//!
//! \param  None
//!
//! \return None
//
//*****************************************************************************
static void
BoardInit(void)
{
/* In case of TI-RTOS vector table is initialize by OS itself */
#ifndef USE_TIRTOS
    //
    // Set vector table base
    //
#if defined(ccs)
    MAP_IntVTableBaseSet((unsigned long)&g_pfnVectors[0]);
#endif
#if defined(ewarm)
    MAP_IntVTableBaseSet((unsigned long)&__vector_table);
#endif
#endif
    //
    // Enable Processor
    //
    MAP_IntMasterEnable();
    MAP_IntEnable(FAULT_SYSTICK);

    PRCMCC3200MCUInit();
}

int
read_reg() {


    const unsigned char setup[3] = {0b00000001, 0b01000010, 0b11100010};
    const unsigned char add = 0b00000000;
    unsigned char buffer[2];


    I2C_IF_Write(0x48, setup, 3,0);
    I2C_IF_Write(0x48, &add, 1,0);
    I2C_IF_Read(0x48, buffer, 2);

    int16_t result = (buffer[0] << 8) | buffer[1];

    return result;
}

#define NUM_READINGS 100

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}


void main()
{

    BoardInit();
    PinMuxConfig();

    InitTerm();
    ClearTerm();

    I2C_IF_Open(I2C_MASTER_MODE_FST);


    AWSIoT_init();
    Clock_init();
    Machine_init();
    UI_init();


    //AWSIoT_sendEmail("Hello: email 1");
    //AWSIoT_sendEmail("Hello: email 2");

    Report("\n\r Starting...");
    while (FOREVER) {

        UI_step();

        Machine_step();


//        int readings[NUM_READINGS];
//        int i;
//
//        for (i = 0; i < NUM_READINGS; i++) {
//            readings[i] = read_reg();
//            MAP_UtilsDelay(MILLISECONDS_TO_TICKS(10) / 3);
//        }
//
//        // Sort the readings array
//        qsort(readings, NUM_READINGS, sizeof(int), compare);
//
//        // Calculate the median
//        int median;
//        if (NUM_READINGS % 2 == 0) {
//            median = (readings[NUM_READINGS / 2 - 1] + readings[NUM_READINGS / 2]) / 2;
//        } else {
//            median = readings[NUM_READINGS / 2];
//        }
//
//        Report("\n\r Median Reading: %d", median);
//


    }

}



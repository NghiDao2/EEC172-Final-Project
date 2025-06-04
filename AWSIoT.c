/*
 * AWSIoT.c
 *
 *  Created on: May 27, 2025
 *      Author: daomi
 */

#include <Scanner/Machine.h>   // for MAX_SCANS_PER_LAYER
#include <stdio.h>

// Simplelink includes
#include "simplelink.h"

//Driverlib includes
#include "hw_types.h"
#include "hw_ints.h"
#include "rom.h"
#include "rom_map.h"
#include "interrupt.h"
#include "prcm.h"
#include "utils.h"
#include "uart.h"

#include "interrupt.h"
#include "hw_apps_rcm.h"
#include "hw_common_reg.h"
#include "prcm.h"
#include "rom.h"
#include "hw_memmap.h"
#include "spi.h"
#include "timer.h"
#include "gpio.h"


//Common interface includes
#include "pin_mux_config.h"
#include "gpio_if.h"
#include "common.h"
#include "uart_if.h"

#include "timer_if.h"
#include "gpio_if.h"

#include "uart_if.h"

// Custom includes
#include "utils/network_utils.h"
#include <AWSIoT.h>



static long lRetVal;    // TLS socket ID

void AWSIoT_init() {
    lRetVal = -1;
    // initialize global default app configuration
    g_app_config.host = SERVER_NAME;
    g_app_config.port = GOOGLE_DST_PORT;
    // connect WiFi
    lRetVal = connectToAccessPoint();
    // set time for TLS
    if (AWSIoT_set_time() < 0) {
        UART_PRINT("Unable to set time in the device\n\r");
        LOOP_FOREVER();
    }
    // open TLS
    lRetVal = tls_connect();
    if (lRetVal < 0) {
        ERR_PRINT(lRetVal);
        LOOP_FOREVER();
    }
}


void AWSIoT_sendEmail(const char *msg) {
    char* json = AWSIoT_build_email(msg);
    AWSIoT_http_post(lRetVal, json);
    free(json);

}

char* AWSIoT_build_email(const char* msg) {
    const char* fmt =
        "{\n"
        "    \"state\": {\n"
        "        \"desired\": {\n"
        "            \"default\": \"\",\n"
        "            \"email\": \"%s\"\n"
        "        }\n"
        "    }\n"
        "}\r\n\r\n";

    char* json = malloc(snprintf(NULL, 0, fmt, msg) + 1);
    if (json) sprintf(json, fmt, msg);
    return json;
}


int AWSIoT_set_time() {
    long retVal;
    // configure g_time from CONFIG.H DATE/MONTH/YEAR/HOUR/MINUTE/SECOND
    g_time.tm_day  = DATE;
    g_time.tm_mon  = MONTH;
    g_time.tm_year = YEAR;
    g_time.tm_sec  = HOUR;
    g_time.tm_hour = MINUTE;
    g_time.tm_min  = SECOND;
    retVal = sl_DevSet(
      SL_DEVICE_GENERAL_CONFIGURATION,
      SL_DEVICE_GENERAL_CONFIGURATION_DATE_TIME,
      sizeof(SlDateTime),
      (unsigned char *)(&g_time)
    );
    ASSERT_ON_ERROR(retVal);
    return SUCCESS;
}

#define MAX_SEND_SIZE 1024

int AWSIoT_http_post(int iTLSSockID, const char* json) {
    char acSendBuff[2048];  // Enough space for headers + body
    char acRecvbuff[1460];
    char cCLLength[200];
    char* pcBufHeaders;
    int lRetVal = 0;

    // Compose headers
    pcBufHeaders = acSendBuff;
    strcpy(pcBufHeaders, POSTHEADER);
    pcBufHeaders += strlen(POSTHEADER);
    strcpy(pcBufHeaders, HOSTHEADER);
    pcBufHeaders += strlen(HOSTHEADER);
    strcpy(pcBufHeaders, CHEADER);
    pcBufHeaders += strlen(CHEADER);
    strcpy(pcBufHeaders, CTHEADER);
    pcBufHeaders += strlen(CTHEADER);
    strcpy(pcBufHeaders, CLHEADER1);
    pcBufHeaders += strlen(CLHEADER1);

    // Content-Length
    int dataLength = strlen(json);
    sprintf(cCLLength, "%d", dataLength);
    strcpy(pcBufHeaders, cCLLength);
    pcBufHeaders += strlen(cCLLength);
    strcpy(pcBufHeaders, CLHEADER2);
    pcBufHeaders += strlen(CLHEADER2);

    // End of headers
    strcpy(pcBufHeaders, "\r\n\r\n");
    pcBufHeaders += strlen("\r\n\r\n");

    // Add body
    strcpy(pcBufHeaders, json);
    pcBufHeaders += strlen(json);

    int totalLength = pcBufHeaders - acSendBuff;

    UART_PRINT("Total POST size: %d bytes\n\r", totalLength);

    // Send in chunks of 1024 bytes
    int bytesSent = 0;
    while (bytesSent < totalLength) {
        int bytesToSend = totalLength - bytesSent;
        if (bytesToSend > MAX_SEND_SIZE) {
            bytesToSend = MAX_SEND_SIZE;
        }

        lRetVal = sl_Send(iTLSSockID, acSendBuff + bytesSent, bytesToSend, 0);
        if (lRetVal < 0) {
            UART_PRINT("POST failed. Error Number: %i\n\r", lRetVal);
            sl_Close(iTLSSockID);
            return lRetVal;
        }

        UART_PRINT("Sent %d bytes\n\r", lRetVal);
        bytesSent += lRetVal;
    }

    // Receive response
    lRetVal = sl_Recv(iTLSSockID, &acRecvbuff[0], sizeof(acRecvbuff), 0);
    if (lRetVal < 0) {
        UART_PRINT("Receive failed. Error Number: %i\n\r", lRetVal);
        return lRetVal;
    } else {
        acRecvbuff[lRetVal+1] = '\0';
        UART_PRINT(acRecvbuff);
        UART_PRINT("\n\r\n\r");
    }

    Report("\n\rFinished posting\n\r");
    return 0;
}



/*––– NEW: Build & POST initial scan config –––*/
char* AWSIoT_build_scan_config(int scans, int layers) {
    const char* fmt =
      "{\n"
      "  \"state\": {\n"
      "    \"desired\": {\n"
      "      \"layer\": 0,\n"
      "      \"scansPerLayer\": %d,\n"
      "      \"layersPerMM\": %d,\n"
      "      \"finished\": false\n"
      "    }\n"
      "  }\n"
      "}\r\n\r\n";
    int len = snprintf(NULL, 0, fmt, scans, layers) + 1;
    char* buf = malloc(len);
    if (buf) sprintf(buf, fmt, scans, layers);
    return buf;
}

void AWSIoT_updateScanConfig(int scans, int layers) {
    char* j = AWSIoT_build_scan_config(scans, layers);
    AWSIoT_http_post(lRetVal, j);
    free(j);
}

/*––– NEW: Build & POST single-layer result –––*/
char* AWSIoT_build_layer_result(int layer,
                                int16_t *data,
                                int count,
                                float zPos,
                                bool finished)
{
    // first build the newline-separated readings
    int    bufSz = count * 8 + 32;
    char*  readings = malloc(bufSz);
    if (!readings) return NULL;
    readings[0] = '\0';

    int i;
    for (i = 0; i < count; ++i) {
        char line[16];
        snprintf(line, sizeof(line), "%d,", data[i]);
        strcat(readings, line);
    }
    // now embed into JSON
    const char* fmt =
      "{\n"
      "  \"state\": {\n"
      "    \"desired\": {\n"
      "      \"layer\": %d,\n"
      "      \"data\": \"%s\",\n"
      "      \"height\": \"%.6f\",\n"
      "      \"finished\": \"%s\"\n"
      "    }\n"
      "  }\n"
      "}\r\n\r\n";

    int len = snprintf(NULL, 0, fmt,
                       layer,
                       readings,
                       zPos,
                       finished ? "true" : "false")
            + 1;
    char* buf = malloc(len);
    if (buf) sprintf(buf, fmt,
                     layer,
                     readings,
                     zPos,
                     finished ? "true" : "false");
    free(readings);
    return buf;
}

void AWSIoT_sendLayerResult(int layer,
                            int16_t *data,
                            int count, float zPos,
                            bool finished)
{
    char* j = AWSIoT_build_layer_result(layer, data, count, zPos, finished);
    if (j) {

        AWSIoT_http_post(lRetVal, j);
        free(j);
    }
}

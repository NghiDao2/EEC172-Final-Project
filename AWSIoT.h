/*
 * AWSIoT.h
 *
 *  Created on: May 27, 2025
 *      Author: daomi
 */

#ifndef SCANNER_AWSIOT_H_
#define SCANNER_AWSIOT_H_

#include <stdint.h>
#include <stdbool.h>

//NEED TO UPDATE THIS FOR IT TO WORK!
#define DATE                3    /* Current Date */
#define MONTH               6     /* Month 1-12 */
#define YEAR                2025  /* Current year */
#define HOUR                1    /* Time - hours */
#define MINUTE              00    /* Time - minutes */
#define SECOND              00     /* Time - seconds */


#define APPLICATION_NAME      "SSL"
#define APPLICATION_VERSION   "SQ24"
#define SERVER_NAME           "a2sylnw4ig33dq-ats.iot.us-east-1.amazonaws.com" // CHANGE ME
#define GOOGLE_DST_PORT       8443


#define POSTHEADER "POST /things/CC3200_Board_Thing/shadow HTTP/1.1\r\n"             // CHANGE ME
#define HOSTHEADER "Host: a2sylnw4ig33dq-ats.iot.us-east-1.amazonaws.com\r\n"  // CHANGE ME
#define CHEADER "Connection: close\r\n"
#define CTHEADER "Content-Type: application/json; charset=utf-8\r\n"
#define CLHEADER1 "Content-Length: "
#define CLHEADER2 "\r\n\r\n"


/*
 * Initialize AWS IoT:
 *   – connect WiFi
 *   – set device time for TLS
 *   – open TLS socket
 */
void AWSIoT_init(void);

/*
 * Send a generic email notification by updating "email" desired key.
 * Allocates a small JSON, posts it, then frees.
 */
void AWSIoT_sendEmail(const char *msg);

/*
 * Update the shadow with initial scan configuration:
 *   desired.scansPerLayer = scans
 *   desired.layersPerMM   = layers
 *   desired.finished      = false
 */
void AWSIoT_updateScanConfig(int scansPerLayer, int layersPerMM);


void AWSIoT_sendLayerResult(int layer,
                            int16_t *data,
                            int count,
                            float zPos,
                            bool finished);

/*
 * Low-level HTTP POST over the existing TLS socket.
 * Returns 0 on success, or negative SL error.
 */
int  AWSIoT_http_post(int sockID, const char *json);

/*
 * Set the SimpleLink device time for TLS.
 * Returns 0 on success.
 */
int  AWSIoT_set_time(void);


#endif /* SCANNER_AWSIOT_H_ */

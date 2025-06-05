/*
 * gps_parser.h
 *
 *  Created on: Mar 22, 2025
 *      Author: 91748
 */

#ifndef INC_GPS_PARSER_H_
#define INC_GPS_PARSER_H_

// Includes
#include "globals.h"
#include "stdio.h"
#include "lorawan_version.h"
#include "subghz_phy_version.h"
#include "lora_info.h"
#include "LmHandler.h"
#include "stm32_lpm.h"

// Variables

// Prototypes
void packet_checking_func(uint8_t* uart_rx_buffer);
void parse_nmea_sentence(uint8_t *nmea_sentence, char *latitude, char *longitude);
float convertToDecimalDegrees(float);


#endif /* INC_GPS_PARSER_H_ */

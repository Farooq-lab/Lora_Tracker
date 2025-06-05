/*
 * Gps.h
 *
 *  Created on: Jun 5, 2025
 *      Author: Hariharan Veerappan
 */
#ifndef _GPS_H
#define _GPS_H

#include "main.h"
#include "gps_parser.h"
#include "stdlib.h"

extern UART_HandleTypeDef huart2;

void Get_Gps_Coordinates(void);


#endif /*_GPS_H */


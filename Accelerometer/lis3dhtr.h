/*
 * lis3dhtr.h
 *
 *  Created on: Jun 5, 2025
 *      Author: Hariharan Veerappan
 */

#ifndef INC_LIS3DHTR_H
#define INC_LIS3DHTR_H

#include  "main.h"
#include  "stdbool.h"
#include "stdio.h"
#include "string.h"

// Creating a type -->  AccValues_t
typedef struct
{
	float x_accel ;
	float y_accel ;
	float z_accel ;
}AccValues_t;

void lis3dh_init(void) ;
void lis3dh_setODR(uint8_t odr) ;
void lis3dh_readData(void) ;
void lis3dh_calc_value(uint16_t raw_value, float *final_value, bool isAccel);
void  who_am_i_read(void);
AccValues_t readAccelerationDataXYZ(void);


#endif /* INC_LIS3DHTR_H */

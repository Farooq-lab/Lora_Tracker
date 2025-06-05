/*
 * Gps.c
 *
 *  Created on: Jun 5, 2025
 *      Author: Hariharan Veerappan
 */
#include "Gps.h"

char lat[16] = {0};
char lon[16] = {0};
float latit = 0.0, longit = 0.0;

/* ---------- Emergency Button Interrupt Callback STARS HERE ----------*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	switch(GPIO_Pin){
	case BUT1_Pin:
		BTN_FLAG =  1;					// Enable the Button Flag
		break;
	default:
		break;
	}
}

/* ---------- Emergency Button Interrupt Callback ENDS HERE ----------*/

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	if(huart->Instance == USART2){
		  HAL_UARTEx_ReceiveToIdle_IT(&huart2, uart_rx_buffer, sizeof(uart_rx_buffer));
		  GPS_FLAG = 1;
	}
}

/* Function that continuously acquires GPS Data */
void Get_Gps_Coordinates()
{
	packet_checking_func(uart_rx_buffer); 				// Extract data from the UART

	printf("GPS DATA  :  %s\r\n",(char*)Extracted_Data);

	parse_nmea_sentence(Extracted_Data, lat, lon); 		// Parse latitude and longitude --> Filtration : Lat , Long
	printf("Parsed LATITUDE : %s , LONGITUDE : %s\r\n", lat , lon);	// Print latitude and longitude (for debugging)


	// Ensure Valid GPS data is stored
	if(lat[0] != '\0' && lon[0] != '\0' && atof(lat) != 0.0 && atof(lon) != 0.0)
	{
		latit = convertToDecimalDegrees(atof(lat));							// Store it in variables to send as a payload later
		longit = convertToDecimalDegrees(atof(lon));
		GPS_READY = 1 ;  													// Set flag to indicate valid data
	}
	else
	{
		GPS_READY = 0 ;
	}

	GPS_FLAG = 0 ;    																// Reset the flag so that the same nmea sentence is'nt used repeatedly
}

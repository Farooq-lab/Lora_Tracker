/*
 * lora_comm.c
 *
 *  Created on: Mar 22, 2025
 *      Author: 91748
 */

// Includes
#include "globals.h"
#include "lora_comm.h"
#include "main.h"
#include "gps_parser.h"

extern volatile int gpsDataReady;

#define APP_DATA_BUFFER_MAX_SIZE 64

#define LORA_SUCCESS  0
#define LORA_FAIL     -1

char latitude[16] = {0};
char longitude[16] = {0};
float lati = 0.0, longi = 0.0;
//char payload[512] = {0};

uint8_t AppDataBuffer[APP_DATA_BUFFER_MAX_SIZE];
LmHandlerAppData_t AppData = { 0, 0, AppDataBuffer };

int sendLoRaTxData(const char* payload , bool confirmed)
{
	printf("*****Lora Payload to things network*****:%s\n",payload);
	strncpy((char *)AppData.Buffer , payload , strlen(payload));
	//AppData.Buffer[sizeof(AppData.Buffer) - 1] = '\0';
	AppData.BufferSize = strlen(payload);
	AppData.Port = 2 ;

//	if(confirmed)
//	{
//		loRaAckReceived  = 0 ;																	// Reset Acknowledgment Status
//	}


	// Send the data with Confirmed ? UnConfirmed FLag
//	if(LmHandlerSend(&AppData, confirmed ? LORAMAC_HANDLER_CONFIRMED_MSG : LORAMAC_HANDLER_UNCONFIRMED_MSG, true) == LORAMAC_HANDLER_SUCCESS)
//	{
//		printf("SEND REQUEST : %s \r\n" , payload);
//		if(confirmed)																			// wait for Acknowledgment (Only for Confirmed messages)
//		{
//			uint32_t startTime = HAL_GetTick();
//			while((HAL_GetTick() - startTime) < 5000)
//			{
//				if (loRaAckReceived)  															// Check if ACK is received or failed
//				{
//                    printf("LoRa TX Confirmed!\r\n");
//                    return LORA_SUCCESS;
//				}
//			}
//            printf("LoRa TX Failed - No ACK!\r\n");
//            return LORA_FAIL;
//		}
//		return LORA_SUCCESS ;
//	}
//	else
//	{
//		printf("LoRa Tx Failed\r\n");
//		return LORA_FAIL ;
//	}
//


		printf("SEND REQUESTb 1 : %s \r\n" , (char *)AppData.Buffer);

		LmHandlerErrorStatus_t ret = LmHandlerSend(&AppData, confirmed ? LORAMAC_HANDLER_CONFIRMED_MSG : LORAMAC_HANDLER_UNCONFIRMED_MSG, false);
		printf("Handler return : %d\r\n",ret);
		//LoRaTxConfirmCallBack(true);
		if (ret == LORAMAC_HANDLER_SUCCESS)  															// Check if ACK is received or failed
		{
			printf("LoRa TX Confirmed!\r\n");
							HAL_GPIO_WritePin(GPIOA , GPIO_PIN_10 , GPIO_PIN_SET);				// Turn On BUZZER only after Acknowledgment
							HAL_Delay(500);
							HAL_GPIO_WritePin(GPIOA , GPIO_PIN_10 , GPIO_PIN_RESET);
			return LORA_SUCCESS;
		}
		else
		{
			printf("LoRa Tx Failed\r\n");
			return LORA_FAIL;
		}

}

//void LoRaTxConfirmCallBack(bool ackRecieved)					// Sets the flag based on the acknowledgment received
//{
//	if(ackRecieved)
//	{
//		loRaAckReceived = 1 ;
//	}
//	else
//	{
//		loRaAckReceived = -1 ;									// Transmission Failure
//	}
//}

/*	SendEmergencyData()
 *  	Sends latest GPS Data over the LoRa thrice .
 * 		After each successful transmission (with acknowledgment) , the buzzer beeps
 *  */
void sendEmergencyData()
{
//	if(!gpsDataReady)
//	{
//		printf("No Valid GPS data yet . PLEASE WAIT ...\r\n");
//		return ;                                                         			// Do not send if no valid GPS fix..
//	}
	char payload[512] = {0};
	snprintf(payload , sizeof(payload) , "%.4f,%.4f" , lati , longi);
	printf("*****Lora Payload*****:%s\n",payload);

	for(int i = 0 ; i < 3 ; i++)
	{
		//HAL_Delay(5000);
		for(int j=0; j < 10000; j++){
			MX_LoRaWAN_Process();
		}

//		snprintf(payload , sizeof(payload) , "%.4f,%.4f" , lati , longi);
		//loRaAckReceived = 0 ; 														// Reset Acknowledgment flag
		if(sendLoRaTxData(payload , false) == LORA_SUCCESS)
		{
			printf("Data Sent successfully\r\n");

//			uint32_t timeout = HAL_GetTick() + 5000 ;								// Wait for Acknowledgment ..consider 5 seconds of buffer time
//			while(loRaAckReceived == 0 && HAL_GetTick() < timeout);
//			if(loRaAckReceived == 1)
//			{
//				printf("LoRa Acknowledgment Received Successfully !!! \r\n");
//				HAL_GPIO_WritePin(GPIOA , GPIO_PIN_10 , GPIO_PIN_SET);				// Turn On BUZZER only after Acknowledgment
//				HAL_Delay(500);
//				HAL_GPIO_WritePin(GPIOA , GPIO_PIN_10 , GPIO_PIN_RESET);
//			}
//			else
//			{
//				printf("LoRa Transmission FAILED \r\n");
//			}
		}
		else
		{
			printf("LoRa Transmission Failed at initial send ...\r\n");
		}
	}
}

/* Function that continuously acquires GPS Data */
void updateGPSData()
{
//	char* whole_single_packet_data = packet_checking_func(uart_rx_buffer); 		// Extract GNRMC sentence --> PacketCheckingFunction
//	printf("GPS DATA  :  %s\r\n",whole_single_packet_data);
//	parse_nmea_sentence(whole_single_packet_data, latitude, longitude); 		// Parse latitude and longitude --> Filtration : Lat , Long
//	printf("Parsed LATITUDE : %s , LONGITUDE : %s\r\n", latitude , longitude);	// Print latitude and longitude (for debugging)
//
//
//	// Ensure Valid GPS data is stored
//	if(latitude[0] != '\0' && longitude[0] != '\0' && atof(latitude) != 0.0 && atof(longitude) != 0.0)
//	{
//		lati = convertToDecimalDegrees(atof(latitude));							// Store it in variables to send as a payload later
//		longi = convertToDecimalDegrees(atof(longitude));
//		gpsDataReady = 1 ;  													// Set flag to indicate valid data
//	}
//	else
//	{
//		gpsDataReady = 0 ;
//	}
//
//	GPS_FLAG = 0 ;    																// Reset the flag so that the same nmea sentence is'nt used repeatedly
}

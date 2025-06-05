/*
 * gps_parser.c
 *
 *  Created on: Mar 22, 2025
 *      Author: 91748
 */

// Includes
#include "main.h"
#include "stdio.h"
#include "string.h"
#include "gps_parser.h"

#define MAX_SENTENCE_SIZE 150

// Extract the GNRMC sentence from the UART buffer
void packet_checking_func(uint8_t* uart_rx_buffer)
{
    char *start_ptr = NULL;
    char *asterisk_ptr = NULL;
	int sentence_length = 0;

	start_ptr = strstr((char *)uart_rx_buffer, "$GNRMC");

	asterisk_ptr = strchr((char *)uart_rx_buffer, '*');

    if (start_ptr != NULL)
    {
        asterisk_ptr = strchr(start_ptr, '*');

        if (asterisk_ptr != NULL){

            sentence_length = (asterisk_ptr - start_ptr) + 3;  // *XX => +3

            if (sentence_length < MAX_SENTENCE_SIZE && (asterisk_ptr - (char *)uart_rx_buffer) < BUFFER_SIZE)
            {
                memcpy(Extracted_Data, start_ptr, sentence_length);
                Extracted_Data[sentence_length] = '\0';  // Null-terminate
            }
        }
	}
}

// Parse the NMEA sentence to extract latitude and longitude
void parse_nmea_sentence(uint8_t *nmea_sentence, char *latitude, char *longitude)
{
	char *token;
	int field_index = 0;

//	memcpy(sentence_copy, nmea_sentence, SINGLE_PACKET_DATA_SIZE);										// Copy the NMEA sentence to a local buffer
	token = strtok((char*)nmea_sentence, ",");																	// Tokenize the sentence using commas as delimiters

	while (token != NULL)
	{
		field_index++;

		if (field_index == 4)																			// Extract latitude (4th field)
		{
			strncpy(latitude, token, 9); 																// Latitude is up to 9 characters (e.g., 4807.038)
			latitude[9] = '\0'; 																		// Null-terminate the string
		}
		if (field_index == 6)																			// Extract longitude (6th field)
		{
			strncpy(longitude, token, 10); 																// Longitude is up to 10 characters (e.g., 01131.000)
			longitude[10] = '\0'; 																		// Null-terminate the string
		}
		token = strtok(NULL, ",");																		// Move to the next token
	}
}

float convertToDecimalDegrees(float nmea_value)
{
	int degrees = (int)(nmea_value / 100);
	float minutes = nmea_value - (degrees * 100);

	return degrees + (minutes / 60);
}

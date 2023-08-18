/*
 * pzem004t.c
 *
 *  Created on: Aug 3, 2023
 *  Author: Md. Khairul Alam
 */


#include "pzem004t.h"
#include <stdio.h>

uint8_t buf[8] = {0xF8, 0x04, 0x00, 0x00, 0x00, 0x0A, 0x64, 0x64};
uint8_t rst_buf[4] = {0xF8, 0x42, 0xC2, 0x41};
uint8_t res_buf[25];

void read_pzem004t(pzem_values *currentValues, UART_HandleTypeDef *huart)
{
	currentValues->huart = huart;
	HAL_Delay(100);
    HAL_UART_Transmit(currentValues->huart, (uint8_t*) &rst_buf, 4, 10);
    HAL_UART_Receive(currentValues->huart, res_buf, 25, 250);
    HAL_Delay(100);
    HAL_UART_Transmit(currentValues->huart, (uint8_t*) &buf, 8, 20);
	HAL_UART_Receive(currentValues->huart, res_buf, 25, 250);

	currentValues->voltage = ((uint32_t) res_buf[3] << 8 | (uint32_t) res_buf[4]) / 10;
	currentValues->current = ((uint32_t) res_buf[5] << 8 | (uint32_t) res_buf[6] | (uint32_t) res_buf[7] << 24 |
							(uint32_t) res_buf[8] << 16) / 1000.0;
	currentValues->power = ((uint32_t) res_buf[9] << 8 | (uint32_t) res_buf[10] | (uint32_t) res_buf[11] << 24 |
						  (uint32_t) res_buf[12] << 16) / 10.0;
	currentValues->energy = ((uint32_t) res_buf[13] << 8 | (uint32_t) res_buf[14] | (uint32_t) res_buf[15] << 24 |
						   (uint32_t) res_buf[16] << 16) / 1000.0;
	currentValues->frequency = ((uint32_t) res_buf[17] << 8 | (uint32_t) res_buf[18]) / 10.0;
	currentValues->pf = ((uint32_t) res_buf[19] << 8 | (uint32_t) res_buf[20]) / 100.0;
	currentValues->alarms = ((uint32_t) res_buf[21] << 8 | (uint32_t) res_buf[22]);

	memset(res_buf,0,sizeof(res_buf));

}

void print_pzem004t(pzem_values *currentValues)
{
	int volt = (int) currentValues->voltage;
	int voltf = (currentValues->voltage * 100 - volt)/1000;
	int cur = (int) currentValues->current;
	int curf = currentValues->current * 100 - cur;
	int pow = (int) currentValues->power;
	int powf = (currentValues->power * 100 - pow)/10;
	int eng = (int) currentValues->energy;
	int engf = currentValues->energy * 100 - eng;
	int freq = (int) currentValues->frequency;
	int freqf = (currentValues->frequency * 100 - freq)/100;
	int pf = (int) currentValues->pf;
	int pff = currentValues->pf * 100 - pf;

	printf("--------------------------------------------\n");
	printf("Voltage = %d.%d Volt\n", volt, voltf);
	printf("Current = %d.%d Amps\n", cur, curf);
	printf("Power = %d.%d Watt\n", pow, powf);
	printf("Energy = %d.%d KWh\n", eng, engf);
	printf("Frequency = %d.%d Hz\n", freq, freqf);
	printf("Pf = 0.%d\n", pff);
	printf("--------------------------------------------\n");
}


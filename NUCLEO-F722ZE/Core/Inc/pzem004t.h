/*
 * pzem004t.h
 *
 *  Created on: Aug 3, 2023
 *  Author: Md. Khairul Alam
 */

#ifndef INC_PZEM004T_H_
#define INC_PZEM004T_H_

#include "main.h"
#include "stdio.h"
#include "string.h"

#define PZEM_DEFAULT_ADDR   0x01
#define PZEM_BAUD_RATE      9600

#define REG_VOLTAGE     0x0000
#define REG_CURRENT_L   0x0001
#define REG_CURRENT_H   0X0002
#define REG_POWER_L     0x0003
#define REG_POWER_H     0x0004
#define REG_ENERGY_L    0x0005
#define REG_ENERGY_H    0x0006
#define REG_FREQUENCY   0x0007
#define REG_PF          0x0008
#define REG_ALARM       0x0009

#define CMD_RHR         0x03
#define CMD_RIR         0X04
#define CMD_WSR         0x06
#define CMD_CAL         0x41
#define CMD_REST        0x42

#define WREG_ALARM_THR   0x0001
#define WREG_ADDR        0x0002

#define UPDATE_TIME     200

#define RESPONSE_SIZE 32
#define READ_TIMEOUT 100

#define INVALID_ADDRESS 0x00


typedef struct {
	float voltage;
	float current;
	float power;
	float energy;
	float frequency;
	float pf;
	uint16_t alarms;
	UART_HandleTypeDef *huart;
} pzem_values;

void read_pzem004t(pzem_values *currentValues, UART_HandleTypeDef *huart);
void print_pzem004t(pzem_values *currentValues);

#endif /* INC_PZEM004T_H_ */

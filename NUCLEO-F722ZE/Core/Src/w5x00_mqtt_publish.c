/**
 * Copyright (c) 2023 WIZnet Co.,Ltd
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*
 * ----------------------------------------------------------------------------------------------------
 * Includes
 * ----------------------------------------------------------------------------------------------------
 */
#include "main.h"
#include <stdio.h>
#include <string.h>

#include "wizchip_conf.h"
#include "w5x00_network.h"
#include "w5x00_timer.h"
#include "w5x00_mqtt_info.h"

#include "mqtt_interface.h"
#include "MQTTClient.h"

/*
 * ----------------------------------------------------------------------------------------------------
 * Macros
 * ----------------------------------------------------------------------------------------------------
 */

/*
 * ----------------------------------------------------------------------------------------------------
 * Variables
 * ----------------------------------------------------------------------------------------------------
 */
static uint8_t g_mqtt_send_buf[ETHERNET_BUF_MAX_SIZE] = {
    0,
};
static uint8_t g_mqtt_recv_buf[ETHERNET_BUF_MAX_SIZE] = {
    0,
};
static uint8_t g_mqtt_broker_ip[4] = {91, 121, 93, 94};  //public ip of test.mosquitto.org
static Network g_mqtt_network;
static MQTTClient g_mqtt_client;
static MQTTPacket_connectData g_mqtt_packet_connect_data = MQTTPacket_connectData_initializer;
static MQTTMessage g_mqtt_message;

/**
 * ----------------------------------------------------------------------------------------------------
 * Functions
 * ----------------------------------------------------------------------------------------------------
 */

static void repeating_timer_callback(void)
{
  MilliTimer_Handler();
}


static void message_arrived(MessageData *msg_data)
{
  MQTTMessage *message = msg_data->message;

  printf("%.*s receive\n", (uint32_t)message->payloadlen, (uint8_t *)message->payload);

  char *command = message->payload;

  if(strcmp(command, "R1ON") == 0){
	 printf("relay 1 on\n");
	 HAL_GPIO_WritePin(RELAY_1_GPIO_Port, RELAY_1_Pin, GPIO_PIN_SET);
	 return;
  }

  if(strcmp(command, "R1OF") == 0){
	 printf("relay 1 off\n");
  	 HAL_GPIO_WritePin(RELAY_1_GPIO_Port, RELAY_1_Pin, GPIO_PIN_RESET);
	 return;
  }

  if(strcmp(command, "R2ON") == 0){
	 printf("relay 2 on\n");
  	 HAL_GPIO_WritePin(RELAY_2_GPIO_Port, RELAY_2_Pin, GPIO_PIN_SET);
	 return;
  }

  if(strcmp(command, "R2OF") == 0){
	 printf("relay 2 off\n");
     HAL_GPIO_WritePin(RELAY_2_GPIO_Port, RELAY_2_Pin, GPIO_PIN_RESET);
	 return;
  }

  if(strcmp(message->payload, "R3ON") == 0){
	 printf("relay 3 on\n");
  	 HAL_GPIO_WritePin(RELAY_3_GPIO_Port, RELAY_3_Pin, GPIO_PIN_SET);
  	 return;
  }

  if(strcmp(message->payload, "R3OF") == 0){
	 printf("relay 3 off\n");
     HAL_GPIO_WritePin(RELAY_3_GPIO_Port, RELAY_3_Pin, GPIO_PIN_RESET);
     return;
  }

  if(strcmp(message->payload, "R4ON") == 0){
	 printf("relay 4 on\n");
  	 HAL_GPIO_WritePin(RELAY_4_GPIO_Port, RELAY_4_Pin, GPIO_PIN_SET);
  	 return;
  }

  if(strcmp(message->payload, "R4OF") == 0){
	 printf("relay 4 off\n");
     HAL_GPIO_WritePin(RELAY_4_GPIO_Port, RELAY_4_Pin, GPIO_PIN_RESET);
     return;
  }

  if(strcmp(message->payload, "RAON") == 0){
	 printf("relay all on\n");
  	 HAL_GPIO_WritePin(RELAY_1_GPIO_Port, RELAY_1_Pin, GPIO_PIN_SET);
  	 HAL_GPIO_WritePin(RELAY_2_GPIO_Port, RELAY_2_Pin, GPIO_PIN_SET);
  	 HAL_GPIO_WritePin(RELAY_3_GPIO_Port, RELAY_3_Pin, GPIO_PIN_SET);
  	 HAL_GPIO_WritePin(RELAY_4_GPIO_Port, RELAY_4_Pin, GPIO_PIN_SET);
  	 return;
  }

  if(strcmp(message->payload, "RAOF") == 0){
	 printf("relay all off\n");
     HAL_GPIO_WritePin(RELAY_1_GPIO_Port, RELAY_1_Pin, GPIO_PIN_RESET);
     HAL_GPIO_WritePin(RELAY_2_GPIO_Port, RELAY_2_Pin, GPIO_PIN_RESET);
     HAL_GPIO_WritePin(RELAY_3_GPIO_Port, RELAY_3_Pin, GPIO_PIN_RESET);
     HAL_GPIO_WritePin(RELAY_4_GPIO_Port, RELAY_4_Pin, GPIO_PIN_RESET);
  }

}


uint8_t mqtt_connect(wiz_NetInfo *net_info)
{
  int retval = 0;

  wizchip_network_initialize(net_info);
  wizchip_network_information(net_info);

  NewNetwork(&g_mqtt_network, SOCKET_MQTT);

  retval = ConnectNetwork(&g_mqtt_network, g_mqtt_broker_ip, PORT_MQTT);

  if (retval != 1)
  {
    printf(" Network connect failed\n");

  }

  MQTTClientInit(&g_mqtt_client, &g_mqtt_network, MQTT_TIMEOUT, g_mqtt_send_buf, ETHERNET_BUF_MAX_SIZE, g_mqtt_recv_buf, ETHERNET_BUF_MAX_SIZE);

  g_mqtt_packet_connect_data.MQTTVersion = 3;
  g_mqtt_packet_connect_data.cleansession = 1;
  g_mqtt_packet_connect_data.willFlag = 0;
  g_mqtt_packet_connect_data.keepAliveInterval = MQTT_KEEP_ALIVE;
  g_mqtt_packet_connect_data.clientID.cstring = MQTT_CLIENT_ID;
  g_mqtt_packet_connect_data.username.cstring = MQTT_USERNAME;
  g_mqtt_packet_connect_data.password.cstring = MQTT_PASSWORD;

  retval = MQTTConnect(&g_mqtt_client, &g_mqtt_packet_connect_data);

  if (retval < 0)
  {
    printf(" MQTT connect failed : %d\n", retval);
    return 0;

  }

  printf(" MQTT connected\n");
  return 1;

}


void mqtt_publish(char *new_message)
{
  int retval = 0;

  g_mqtt_message.qos = QOS0;
  g_mqtt_message.retained = 0;
  g_mqtt_message.dup = 0;
  //g_mqtt_message.payload = MQTT_PUBLISH_PAYLOAD;
  g_mqtt_message.payload = new_message;
  g_mqtt_message.payloadlen = strlen(g_mqtt_message.payload);


  if ((retval = MQTTYield(&g_mqtt_client, g_mqtt_packet_connect_data.keepAliveInterval)) < 0)
  {
     printf(" Yield error : %d\n", retval);
  }

  retval = MQTTPublish(&g_mqtt_client, MQTT_PUBLISH_TOPIC, &g_mqtt_message);

  if (retval < 0)
  {
     printf(" Publish failed : %d\n", retval);
  }

  printf(" Published\n");
}


void mqtt_subscribe(wiz_NetInfo *net_info)
{
  int retval = 0;

  wizchip_1msec_timer_initialize(repeating_timer_callback);

  retval = MQTTSubscribe(&g_mqtt_client, MQTT_SUBSCRIBE_TOPIC, QOS0, message_arrived);

  if (retval < 0)
  {
    printf(" Subscribe failed : %d\n", retval);
  }

  printf(" Subscribed\n");

}

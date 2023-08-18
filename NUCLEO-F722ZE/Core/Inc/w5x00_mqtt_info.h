/**
 * Copyright (c) 2023 WIZnet Co.,Ltd
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _W5X00_MQTT_INFO_H_
#define _W5X00_MQTT_INFO_H_

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * ----------------------------------------------------------------------------------------------------
 * Includes
 * ----------------------------------------------------------------------------------------------------
 */

/**
 * ----------------------------------------------------------------------------------------------------
 * Macros
 * ----------------------------------------------------------------------------------------------------
 */
#define SOCKET_MQTT 0
#define PORT_MQTT 1883

#define MQTT_CLIENT_ID "w5300-toe"
#define MQTT_USERNAME NULL
#define MQTT_PASSWORD NULL
#define MQTT_PUBLISH_TOPIC "taifur/home/data"
#define MQTT_PUBLISH_PAYLOAD "Hello, World!"
#define MQTT_PUBLISH_PERIOD (1000 * 10) // unit : millisecond
#define MQTT_SUBSCRIBE_TOPIC "taifur/home/command"
#define MQTT_KEEP_ALIVE 60      // unit : second
#define MQTT_TIMEOUT (1000 * 1) // unit : millisecond

/**
 * ----------------------------------------------------------------------------------------------------
 * Variables
 * ----------------------------------------------------------------------------------------------------
 */

/**
 * ----------------------------------------------------------------------------------------------------
 * Functions
 * ----------------------------------------------------------------------------------------------------
 */

void dhcp_demo(wiz_NetInfo *net_info);
void dns_demo(wiz_NetInfo *net_info);
void http_server_demo(wiz_NetInfo *net_info);
uint8_t mqtt_connect(wiz_NetInfo *net_info);
void mqtt_publish(char *new_message);
void mqtt_subscribe(wiz_NetInfo *net_info);
void mqtt_publish_subscribe_demo(wiz_NetInfo *net_info);
void sntp_demo(wiz_NetInfo *net_info);
void tcp_client_over_ssl_demo(wiz_NetInfo *net_info);
void loopback_demo(wiz_NetInfo *net_info);


#ifdef __cplusplus
}
#endif

#endif /* _W5X00_MQTT_INFO_H_ */

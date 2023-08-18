/*
 * web_page.h
 *
 *  Created on: Aug 14, 2023
 *      Author: khair
 */

#ifndef INC_WEB_PAGE_H_
#define INC_WEB_PAGE_H_

#include "w5x00_network.h"

#define HTTP_SOCKET_MAX_NUM 4

static uint8_t g_http_send_buf[ETHERNET_BUF_MAX_SIZE] = {
    0,
};
static uint8_t g_http_recv_buf[ETHERNET_BUF_MAX_SIZE] = {
    0,
};
static uint8_t g_http_socket_num_list[HTTP_SOCKET_MAX_NUM] = {0, 1, 2, 3};

#define index_page  "<!DOCTYPE html>"\
                    "<html lang=\"en\">"\
                    "<head>"\
                      "<meta charset=\"UTF-8\">"\
                      "<title>HTTP Server Example</title>"\
                    "</head>"\
                    "<body>"\
                      "<h1>Hello, World!</h1>"\
                    "</body>"\
                    "</html>"

#endif /* INC_WEB_PAGE_H_ */

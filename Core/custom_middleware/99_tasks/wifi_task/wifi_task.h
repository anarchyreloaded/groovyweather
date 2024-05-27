/**
 * @file    wifi_task.c
 * @author  Volker Tenta, Patrick Schmitt
 * @version 0.0.1
 * @date    2024-04-29
 *
 * @brief This file contains functions for the wifi-task implementation. AP-Mode.
 * Within this mode the WiFi-Click will act as an access point. Other wifi click (or wifi enabled devices) can than connect to this click module.
 *
 * This very simple Demo initializes the Wifi click in AP-mode and starts an TCP server. Another wifi-click which is in station mode can than connect
 * to this device and establish a TCP connection. This application than checks the receiving data from the wifi click for an "on" or "off" string.
 * This signalizes that an LED on this Nucleo should be switched on or off. A very simple TCP demonstration.
 *
 * For this procedure the application uses simple delays which is really not ideal - we should check here for the replies of the Wifi-Click!
 * Remember that this is only a Demo and not everything is 100% finished. It should only give you a brief starting point for your own implementations!
 *
 * Very simple TCP commands are used to turn on/off an LED at the "server" side (Wifi Click in AP mode)
 *
 *  WARNING! THIS IS A DEMO IMPLEMENTATION! DOES NOT FEATURE ALL ERROR HANDLING / CHECKS!!!
 *
 *  This is only a starting point for your own implementations!
 *
 *  Use this with care - and extend its functionality accordingly!
 *
 */

#ifndef CUSTOM_MIDDLEWARE_99_TASKS_WIFI_TASK_WIFI_TASK_H
#define CUSTOM_MIDDLEWARE_99_TASKS_WIFI_TASK_WIFI_TASK_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "cmsis_os2.h"
#include "usart.h"

#include "../../00_uart_lib/uart.h"
#include "../../01_helper_functions/helper_functions.h"

#define WIFI_TASK_NAME "wifi_task"
#define WIFI_TASK_SIZE 512 * 4
#define WIFI_TASK_PRIORITY osPriorityNormal

void init_wifi_task(void);
void wifiTask_f(void *pvParameters);
HAL_StatusTypeDef send_wifi_command(uint8_t* cmd, uint8_t cmd_size);
void receive_wifi_command(uint8_t* cmd);
void receive_wifi_data_TCP();

#endif //FREERTOS_WIFI_EXAMPLE_WIFI_TASK_H

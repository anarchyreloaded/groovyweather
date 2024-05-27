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

#include "../../99_tasks/wifi_task/wifi_task.h"

extern uint8_t rxBuffer_uart_1[MAX_BUFFER_SIZE];
extern volatile bool is_uart_success;
extern uint8_t uart_buffer[MAX_BUFFER_SIZE];
extern osTimerId_t led_timerHandle;

osThreadId_t wifiTaskHandle;
const osThreadAttr_t wifiTask_attributes = {
		.name = WIFI_TASK_NAME,
		.stack_size = WIFI_TASK_SIZE,
		.priority = (osPriority_t) WIFI_TASK_PRIORITY,
};

//Those variable store the commands of the WiFi-Click which are used in this demo.
uint8_t at_cmd[] = "AT\r\n";
uint8_t restore_factory[] = "AT+RESTORE\r\n";
uint8_t cwstate_cmd[] = "AT+CWSTATE?\r\n";
uint8_t rst_cmd[] = "AT+RST\r\n";
uint8_t set_cwmode_cmd[]  = "AT+CWMODE=2\r\n";
uint8_t set_IP_AP[] = "AT+CIPAP=\"192.168.9.1\",\"192.168.9.1\",\"255.255.255.0\"\r\n";
uint8_t set_cwsap_cmd[]  = "AT+CWSAP=\"ESP_SSID\",\"1234567890\",5,3\r\n";
uint8_t get_cwsap_cmd[] = "AT+CWSAP?\r\n";
uint8_t get_ip_cmd[] = "AT+CIFSR\r\n";
uint8_t start_TCP_server[] = "AT+CIPSERVER=1,5000\r\n";
uint8_t allow_multi_access[] = "AT+CIPMUX=1\r\n";

/**
 * @brief Transmits a command to the Wifi Click using UART1
 *
 * This function transmits a given command by invoking HAL_UART_Transmit with HAL_MAX_DELAY (blocking)
 * It has a simple error check which in case of an error prints a failure message. It does not really handle the error.
 *
 * @param uint8_t *cmd A pointer to the stored command data.
 * @param uint8_t cmd_size The size in bytes of the to be transfered CMD
 *
 * @return HAL_StatusTypeDef This function returns the status code of the HAL_UART_Transmit function.
 */
HAL_StatusTypeDef send_wifi_command(uint8_t* cmd, uint8_t cmd_size) {
	HAL_StatusTypeDef result = HAL_UART_Transmit(&huart1, cmd, cmd_size, HAL_MAX_DELAY);
	if(result != HAL_OK) {
		printf("Sending %s failed with %d\r\n", cmd, result);
	}
	return result;
}

/**
 * @brief Receives a wifi command by checking on flag "is_uart_success" which gets triggered by the UART receive callback.
 *
 * If this flag is true the data from the UART buffer gets printed using printf. The uart_buffer gets flushed.
 * If the flag is false an error message is printed.
 * In both situations the "is_uart_success" flag is set to false.
 *
 * As you can see this function really just prints the received data from the wifi-click and resets the uart flag and the buffer.
 *
 * @param uint8_t *cmd A pointer to the stored command data.
 *
 * @return void This function does not return a value.
 */
void receive_wifi_command(uint8_t* cmd) {
	HAL_Delay(200);
	if(is_uart_success == true) {
		printf("\r\nReceived from %s\r\n", cmd);
		printf("%s\r\n", uart_buffer);
		memset(uart_buffer, 0, MAX_BUFFER_SIZE);
	}
	else {
		printf("\r\nReceiving %s failed\r\n", cmd);
	}
	is_uart_success = false;
}

/**
 * @brief A function which checks the response message of the wifi-click if a TCP packet was received.
 * This function is only used during the TCP receive phase to capture the "on" and "off" messages of the other side of the TCP connection.
 *
 * This only works for this particular situation. A better solution would be to independently monitor the data received by
 * wifi-click to react to other messages as well.
 *
 * @return void This function does not return a value.
 */
void receive_wifi_data_TCP() {
	if(is_uart_success == true) {
		printf("\r\nReceived data %s\r\n", uart_buffer);
		if (strstr((char*)uart_buffer, "on")) {
			green_led_on();
		} else if (strstr((char*)uart_buffer, "off")) {
			green_led_off();
		}
		memset(uart_buffer, 0, MAX_BUFFER_SIZE);
		is_uart_success = false;
	}
	else {
		HAL_Delay(50);
	}
}

/**
 * @brief A function which initializes the wifi-task. It creates the task itself.
 * Clears both UART interfaces (1 and 2) as well as sets the UART1 to receive data.
 *
 * @return void This function does not return a value.
 */
void init_wifi_task(void) {
	printf("wifi_task init\r\n");

	wifiTaskHandle = osThreadNew(wifiTask_f, NULL, &wifiTask_attributes);

	if (wifiTaskHandle == NULL) {
		printf("creating wifi_task_failed\r\n");
	}

	clear_buffer_overflow(&huart1);
	clear_buffer_overflow(&huart2);
	HAL_UARTEx_ReceiveToIdle_IT(&huart1, rxBuffer_uart_1, MAX_BUFFER_SIZE);
}

/**
 * @brief Task function for the wifi-task.
 * During the first call of this task function the wifi-click module gets initialized.
 * "restore_factory" --> set all factory settings to the wifi click to have defined starting point
 * "rst_cmd" --> resets the wifi-click
 * "set_cwmode_cmd" --> sets the wifi-click to act in AP mode
 * "set_cwsap_cmd" --> command to create an WiFi access point
 * "set_IP_AP" --> sets the IP of the AP
 * "allow_multi_access" --> enables multi access to this device
 * "start_TCP_server" --> starts the TCP server
 *
 * Note that the successful execution of those commands is not checked here! --> you will have to implement this!
 *
 * In the while forever loop we are constantly checking if data from the other WiFi-Click was received. If so we switch on/off the LED on
 * the Nucleo (Green LED)
 *
 * @param void *pvParameters Can be used to give the tasks some parameters during execution. Not used here.
 *
 * @return void This function does not return a value.
 */
void wifiTask_f(void *pvParameters) {

	if(send_wifi_command(restore_factory, ARRAY_SIZE(restore_factory)) == HAL_OK) {
		receive_wifi_command(restore_factory);
	}
	HAL_Delay(15000);

	if(send_wifi_command(rst_cmd, ARRAY_SIZE(rst_cmd)) == HAL_OK) {
		receive_wifi_command(rst_cmd);
	}
	HAL_Delay(2000);

	if(send_wifi_command(set_cwmode_cmd, ARRAY_SIZE(set_cwmode_cmd)) == HAL_OK) {
		receive_wifi_command(set_cwmode_cmd);
	}
	HAL_Delay(2000);

	if(send_wifi_command(set_cwsap_cmd, ARRAY_SIZE(set_cwsap_cmd)) == HAL_OK) {
		receive_wifi_command(set_cwsap_cmd);
	}
	HAL_Delay(2000);

	if(send_wifi_command(set_IP_AP, ARRAY_SIZE(set_IP_AP)) == HAL_OK) {
		receive_wifi_command(set_IP_AP);
	}
	HAL_Delay(2000);

	if(send_wifi_command(allow_multi_access, ARRAY_SIZE(allow_multi_access)) == HAL_OK) {
		receive_wifi_command(allow_multi_access);
	}
	HAL_Delay(2000);

	if(send_wifi_command(start_TCP_server, ARRAY_SIZE(start_TCP_server)) == HAL_OK) {
		receive_wifi_command(start_TCP_server);
	}
	HAL_Delay(5000);

	while (1) {

		receive_wifi_data_TCP();
		osDelay(2000);
	}
}

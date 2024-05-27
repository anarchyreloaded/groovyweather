/*
 * wifi_at_base.c
 *
 *  Created on: May 27, 2024
 *      Author: johan
 */


// Konstanten für initial load / startup
uint8_t restore_factory[] = "AT+RESTORE\r\n";
uint8_t cwstate_cmd[] = "AT+CWSTATE?\r\n";
uint8_t rst_cmd[] = "AT+RST\r\n";

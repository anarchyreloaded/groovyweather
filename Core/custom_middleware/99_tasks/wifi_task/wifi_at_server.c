#define MAX_CONNECTIONS 15
//Aus der Demo
			//Those variable store the commands of the WiFi-Click which are used in this demo.
			/*uint8_t at_cmd[] = "AT\r\n";
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
			*/
// Konstanten für die Server Konfiguration  -> Modus + DHCP TCP etc
uint8_t set_cwmode_cmd[]  = "AT+CWMODE=2\r\n";			//Mode 2 = Soft Ap -> strahlt aus

/*
 * Configuriert die SSID ->
 * AT+CWSAP=<ssid>,<pwd>,<chl>,<ecn>[,<max	conn>][,<ssid	hidden>]
 * param 1 -> SSID name
 * param 2 -> PSK
 * param 3 -> wifi channel
 * param 4 -> encryption protocol
 * param 5 -> Anzahl maximaler Connections
 * param 6 -> 0 = Broadcast SSID (default Wert), 1 = Hidden SSID
*/
uint8_t set_cw_soft_ap[] =  "AT+CWSAP=\"SHWM97\",\"SHWM97\",11,3,MAX_CONNECTIONS\r\n";

/*
 * Starte DHCP
 * AT+CWDHCP=<operate>,<mode>
 * param 1 -> 0 = enable, 1 = disable
 * param 2 -> 0 = Station DHCP mode, 1 = Soft AP DHCP Mode
 */



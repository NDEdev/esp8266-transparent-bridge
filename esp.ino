#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <string.h>
#include "SPISlave.h"

// WiFi parameters to be configured
const char* ssid = "Asusnet";
const char* password = "AoDjCEyu";

WiFiUDP udp;

const char *host = "192.168.1.41";
uint16_t	port = 5550;

uint8_t txBuff[32];
int data_ready = 0;
const int ready_to_receive_pin = 4; //GPIO4 High level when it ready to receive

#define READY_TO_RECEIVE() digitalWrite(ready_to_receive_pin,1)
#define POCESSING_RECEIVE() digitalWrite(ready_to_receive_pin,0)

void spi_rx_callback(uint8_t *data, size_t len){
	if(len == 32 && data_ready == 0){
		POCESSING_RECEIVE();
		memcpy(txBuff, data, len);
		data_ready = 1;
	}
}

void setup(void)
{
	pinMode(ready_to_receive_pin, OUTPUT);
	Serial.begin(115200);
	// Connect to WiFi
	Serial.print("Connecting to wifi: Asusnet");
	WiFi.begin(ssid, password);

	// while wifi not connected yet, print '.'
	// then after it connected, get out of the loop
	while (WiFi.status() != WL_CONNECTED) {
	 delay(500);
	 Serial.print(".");
	}
	//print a new line, then print WiFi connected and the IP address
	Serial.println("");
	Serial.println("WiFi connected");
	// Print the IP address
	Serial.println(WiFi.localIP());

	// data has been received from the master. Beware that len is always 32
	// and the buffer is autofilled with zeroes if data is less than 32 bytes long
	// It's up to the user to implement protocol for handling data length

	//bind spi rx callback
	SPISlave.onData(spi_rx_callback);
	SPISlave.begin();
	READY_TO_RECEIVE();
}


void loop() {
	if(data_ready == 1){
		udp.beginPacket(host, port);
		udp.write(txBuff, sizeof(txBuff)-3);
		udp.endPacket();
		memset(txBuff, 0, sizeof(txBuff));
		data_ready = 0;
		READY_TO_RECEIVE();
	}
}

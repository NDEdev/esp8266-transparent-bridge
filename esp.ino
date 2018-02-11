#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <string.h>

// WiFi parameters to be configured
const char* ssid = "Asusnet";
const char* password = "AoDjCEyu";


WiFiUDP udp;

const char *host = "192.168.1.41";
uint16_t	port = 5550;

std::string msg = "Hello PC! Im esp:)";
uint8_t txBuff[150];

void setup(void)
{
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
	msg = "Hello PC! Im esp :)";
	txBuff[0] = 21;
	txBuff[2] = 55;
}

void loop() {
	// Nothing
	udp.beginPacket(host, port);
	udp.write(msg.c_str(), msg.length());
//	udp.write(txBuff, 2);
	udp.endPacket();
	Serial.println("msg send");
	delay(500);

}

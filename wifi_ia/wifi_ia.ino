#include "main.h"
#include <ESP8266WiFi.h>

WiFiServer server(WEB_SERVER_PORT);

void setup() {
//  char      tmpip[IP_LEN];
  boolean   result;
  Serial.begin(115200);
  result = WiFi.softAP(SSID, PASS);
//  WiFi.begin(SSID, PASS);
//  check_connection();
//  memcpy(tmpip, (const void *)WiFi.localIP().toString().c_str(), IP_LEN);
//  Serial.print("IP:");
//  Serial.println(tmpip);
  server.begin();
  delay(1000);
  Serial.println(result);
  
}

void loop() {
    WiFiClient  client;

    client = server.available();
    if (!client) {
        return;
    }
    handle_client(&client);
    delay(1);
}

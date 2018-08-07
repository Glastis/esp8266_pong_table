#include "include/main.h"
#include "include/file_system.h"
#include "include/client.h"
#include <ESP8266WiFi.h>

WiFiServer server(WEB_SERVER_PORT);

void setup()
{
  init_fs();
  Serial.begin(115200);
  WiFi.softAP(SSID, PASS);
  server.begin();
  delay(1000);
}

void loop()
{
    WiFiClient  client;

    client = server.available();
    if (!client)
    {
        delay(1);
        return;
    }
    handle_client(&client);
    delay(1);
}

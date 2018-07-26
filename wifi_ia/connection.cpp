#include "connection.h"
#include <ESP8266WiFi.h>

static void     try_reconnect()
{
  while (WiFi.status() != WL_CONNECTED)
  {
     Serial.print(".");
     delay(RECONNECT_DELAY);
  }
}

void            check_connection()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Connection lost.");
    Serial.println("Reconnecting");
    try_reconnect();
    Serial.println("Connected.");
  }
}

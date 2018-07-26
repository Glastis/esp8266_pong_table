#include "client.h"
#include "utilities.h"

void          handle_client(WiFiClient *client)
{
  char        buffer[BUFFER_LEN];
  String      request;
  
  Serial.println("New client");
  while (!client->available())
  {
      delay(CLIENT_DATA_DELAY);
  }
  request = client->readStringUntil('\r');
  Serial.print("Request: ");
  Serial.println(request);
  client->flush();

  memset(buffer, 0, BUFFER_LEN);
  request.toCharArray(buffer, BUFFER_LEN);
  if (comp_str(buffer, REQUEST_FAVICON))
  {
      client->println(REPONSE_HEADER_NOT_FOUND);
      return;
  }
  client->println(REPONSE_HEADER_OK);
  client->println(REPONSE_HEAD);
  
  client->println(REPONSE_FOOTER);
  client->println(REPONSE_SCRIPT_JS);
}


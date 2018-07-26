#ifndef CLIENT_H_
# define CLIENT_H_

#include <ESP8266WiFi.h>

#define CLIENT_DATA_DELAY   50
#define BUFFER_LEN          1024

const char REQUEST_FAVICON[] =              "GET /favicon.ico";
const char REPONSE_HEADER_NOT_FOUND[] =     "HTTP/1.1 404 Not Found\nContent-Type: text/html\n\n";
const char REPONSE_PAGE_NOT_FOUND[] =       "<!DOCTYPE HTML>\n<html>File not found</html>";
const char REPONSE_HEADER_OK[] =            "HTTP/1.1 200 OK\nContent-Type: text/html\n\n";
const char REPONSE_HEAD[] =                 "<!DOCTYPE HTML>\n<html>\n<head>\n\n</head>\n";
const char REPONSE_FOOTER[] =               "<br>\n<br>\n</html>";
const char REPONSE_SCRIPT_JS[] =            "<script>\n\n</script>";


void                        handle_client(WiFiClient *client);

#endif /* CLIENT_H_ */

#ifndef CLIENT_H_
# define CLIENT_H_

#include <ESP8266WiFi.h>

#define CLIENT_DATA_DELAY                   50u
#define CLIENT_TIMEOUT_DELAY                5000u
#define REQUEST_BUFF_LEN                    512u

const char REQUEST_FAVICON[] =              "GET /favicon.ico";
const char REPONSE_HEADER_NOT_FOUND[] =     "HTTP/1.1 404 Not Found\nContent-Type: text/html\n\n";
const char REPONSE_PAGE_NOT_FOUND[] =       "<!DOCTYPE HTML>\n<html>File not found</html>";

// Header
const char REPONSE_HEADER_HTML_VERSION[] =  "HTTP/1.1";
const char REPONSE_HEADER_CONTENT_TYPE[] =  "Content-Type";
const char REPONSE_HEADER_CONTENT_TEXT[] =  "text/html";
const char REPONSE_HEADER_CONTENT_STYLE[] = "text/css";

// HTTP codes
#define HTTP_CODE_OK_CODE                   200u
const char HTTP_CODE_OK_MESSAGE[] =         "OK";
#define HTTP_CODE_BAD_REQUEST_CODE          400u
const char HTTP_CODE_BAD_REQUEST_MESSAGE[]= "Bad Request";
#define HTTP_CODE_NOT_FOUND_CODE            404u
const char HTTP_CODE_NOT_FOUND_MESSAGE[] =  "Not Found";
#define HTTP_CODE_NOT_ALLOWED_CODE          405u
const char HTTP_CODE_NOT_ALLOWED_MESSAGE[]= "Method Not Allowed";

//Web Pages
const char PAGE_INDEX[] =                   "/index.html";
const char PAGE_NOT_FOUND[] =               "/404.html";

//Http methods
const char METHOD_GET[] =                   "GET";

//Request header
const char REQUEST_HTTP_VERSION[] =         "HTTP";

//DEPRECATED
const char REPONSE_HEADER_OK[] =            "HTTP/1.1 200 OK\nContent-Type: text/html\n\n";
const char REPONSE_HEAD[] =                 ""; //"<!DOCTYPE HTML>\n<html>\n<head>\n\n</head>\n";
const char REPONSE_FOOTER[] =               ""; //"<br>\n<br>\n</html>";
const char REPONSE_SCRIPT_JS[] =            ""; //"<script>\n\n</script>";

struct                  s_req
{
    const char          *http_version;
    const char          *page;
    const char          *method;
};

typedef struct s_req    t_req;

int                     send_page(WiFiClient *client, const char *page);
void                    send_header(WiFiClient *client, unsigned int http_code, const char *http_message, const char *content_type);
int                     handle_client(WiFiClient *client);

#endif /* CLIENT_H_ */

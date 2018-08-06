#include "client.h"
#include "file_system.h"
#include "utilities.h"

void                    send_header(WiFiClient *client, unsigned int http_code, const char *http_message, const char *content_type)
{
    client->print((char *)REPONSE_HEADER_HTML_VERSION);
    client->print(" ");
    client->print((char *)http_code);
    client->print(" ");
    client->println((char *)http_message);
    if (content_type)
    {
        client->print((char *)REPONSE_HEADER_CONTENT_TYPE);
        client->print(": ");
        client->println((char *)content_type);
    }
}

int                     send_page(WiFiClient *client, const char *page)
{
    if (!file_exists(page))
    {
        send_header(client, HTTP_CODE_NOT_FOUND_CODE, HTTP_CODE_NOT_FOUND_MESSAGE, REPONSE_HEADER_CONTENT_TEXT);
        send_page_to_client(client, PAGE_NOT_FOUND);
        return (-1);
    }
    return (send_page_to_client(client, page));
}

int                     is_allowed_http_method(const char *request)
{
    if (strcmp(METHOD_GET, request))
    {
        return (0);
    }
    return (1);
}

static void             parse_request(WiFiClient *client, t_req *req, char *buff)
{
    unsigned int        i;
    unsigned int        sav;

    i = 0;
    Serial.print("Request: ");
    Serial.println(buff);
    req->page = NULL;
    req->method = NULL;
    req->http_version = NULL;
    while (buff[i] && buff[i] != '\n')
    {
        Serial.println(i);
        if (strcmp(&buff[i], REQUEST_HTTP_VERSION))
        {
            Serial.println("HTTP COND");
            sav = i;
            while (buff[i] && buff[i] != '\n' && buff[i] != ' ')
            {
                ++i;
            }
            if (buff[i])
            {
                buff[i] = '\0';
                ++i;
            }
            req->http_version = &buff[sav];
        }
        else if (strcmp(&buff[i], METHOD_GET))
        {
            Serial.println("GET COND");
            req->method = METHOD_GET;
            sav = i;
            while (buff[i] && buff[i] != '\n' && buff[i] != '/')
            {
                ++i;
            }
            if (buff[i] != '/')
            {
                send_header(client, HTTP_CODE_BAD_REQUEST_CODE, HTTP_CODE_BAD_REQUEST_MESSAGE, REPONSE_HEADER_CONTENT_TEXT);
                client->println(HTTP_CODE_BAD_REQUEST_MESSAGE);
            }
            else
            {
                sav = i;
                while (buff[i] && buff[i] != '\n' && buff[i] != ' ')
                {
                    ++i;
                }
                if (buff[i])
                {
                    buff[i] = '\0';
                    ++i;
                }
                req->page = &buff[sav];
            }
        }
        ++i;
    }
}

int                     handle_client(WiFiClient *client)
{
    unsigned int        timout;
    char                buff[REQUEST_BUFF_LEN];
    t_req               req;
    String              request;

    timout = 0;
    Serial.println("New client");
    while (!client->available() && timout < CLIENT_DATA_DELAY)
    {
        delay(CLIENT_DATA_DELAY);
        timout += CLIENT_DATA_DELAY;
    }
    request = client->readStringUntil('\n');
    memcpy(buff, request.c_str(), (request.length() > REQUEST_BUFF_LEN) ? REQUEST_BUFF_LEN : request.length());
    buff[(request.length() > REQUEST_BUFF_LEN) ? REQUEST_BUFF_LEN : request.length()] = '\0';
    parse_request(client, &req, buff);
    client->flush();
    Serial.print("req meth: ");
    Serial.println(req.method);
    Serial.print("req page: ");
    Serial.println(req.page);
    Serial.print("req version: ");
    Serial.println(req.http_version);

    if (req.method == METHOD_GET)
    {
        Serial.println("penis2");
        return (send_page(client, req.page));
    }
    Serial.println("penis3");
    send_header(client, HTTP_CODE_NOT_ALLOWED_CODE, HTTP_CODE_NOT_ALLOWED_MESSAGE, REPONSE_HEADER_CONTENT_TEXT);
    client->println(HTTP_CODE_NOT_ALLOWED_MESSAGE);
    Serial.println("penis4");
    return (-1);
}


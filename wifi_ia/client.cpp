#include "include/client.h"
#include "include/file_system.h"
#include "include/utilities.h"

void                    send_header(WiFiClient *client, unsigned int http_code, const char *http_message, const char *content_type)
{
    client->print(REPONSE_HEADER_HTML_VERSION);
    client->print(" ");
    client->print(http_code);
    client->print(" ");
    client->println(http_message);
    if (content_type)
    {
        client->print(REPONSE_HEADER_CONTENT_TYPE);
        client->print(": ");
        client->println(content_type);
    }
}

int                     send_page(WiFiClient *client, const char *page)
{
    if (page[0] == '/' && !page[1])
    {
        page = PAGE_INDEX;
    }
    if (!file_exists(page))
    {
        Serial.println("Page not found :(");
        send_header(client, HTTP_CODE_NOT_FOUND_CODE, HTTP_CODE_NOT_FOUND_MESSAGE, REPONSE_HEADER_CONTENT_TEXT);
        send_page_to_client(client, PAGE_NOT_FOUND);
        return (-1);
    }
    Serial.println("Page found :)");
    return (send_page_to_client(client, page));
}

static void             parse_request(WiFiClient *client, t_req *req, char *buff)
{
    unsigned int        i;
    unsigned int        sav;
    unsigned int        shifted;

    i = 0;
    req->page = NULL;
    req->method = NULL;
    req->http_version = NULL;
    while (buff[i] && buff[i] != '\n')
    {
        shifted = 0;
        if (comp_str(&buff[i], REQUEST_HTTP_VERSION))
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
            shifted = 1;
            req->http_version = &buff[sav];
        }
        else if (comp_str(&buff[i], METHOD_GET))
        {
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
                shifted = 1;
            }
        }
        if (!shifted)
        {
            ++i;
        }
    }
}

static void             print_request(t_req *req, int endl)
{
    Serial.print("Request method: ");
    Serial.print(req->method);
    Serial.println((endl ? "$" : " "));
    Serial.print("Request page: ");
    Serial.print(req->page);
    Serial.println((endl ? "$" : " "));
    Serial.print("Request version: ");
    Serial.print(req->http_version);
    Serial.println((endl ? "$" : " "));
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
    print_request(&req, 1);

    if (req.method == METHOD_GET)
    {
        return (send_page(client, req.page));
    }
    Serial.println("penis3");
    send_header(client, HTTP_CODE_NOT_ALLOWED_CODE, HTTP_CODE_NOT_ALLOWED_MESSAGE, REPONSE_HEADER_CONTENT_TEXT);
    client->println(HTTP_CODE_NOT_ALLOWED_MESSAGE);
    Serial.println("penis4");
    return (-1);
}


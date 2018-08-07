#include "include/file_system.h"
#include "include/client.h"
#include "FS.h"

void                        init_fs()
{
  SPIFFS.begin();
  SPIFFS.format();
}

int                         file_exists(const char *path)
{
    return (SPIFFS.exists(path) ? 1 : 0);
}

int                         send_page_to_client(WiFiClient *client, const char *page)
{
    char                    buff[FILE_BUFFER_SIZE];
    unsigned int            readed;
    File                    file;

    file = SPIFFS.open(page, "r");
    if (!file)
    {
        send_header(client, HTTP_CODE_NOT_FOUND_CODE, HTTP_CODE_NOT_FOUND_MESSAGE, REPONSE_HEADER_CONTENT_TEXT);
        client->println(HTTP_CODE_NOT_FOUND_MESSAGE);
        return (-1);
    }
    readed = 0;
    while ((readed = file.readBytes(buff, FILE_BUFFER_SIZE - 1)) < FILE_BUFFER_SIZE - 1)
    {
        buff[readed] = '\0';
        client->print(buff);
    }
    file.close();
    return (0);
}


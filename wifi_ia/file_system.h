#ifndef FILE_SYSTEM_H_
# define FILE_SYSTEM_H_

#include <ESP8266WiFi.h>

#define FILE_BUFFER_SIZE    512

void                        init_fs();
int                         file_exists(const char *path);
int                         send_page_to_client(WiFiClient *client, const char *page);

#endif /* FILE_SYSTEM_H_ */

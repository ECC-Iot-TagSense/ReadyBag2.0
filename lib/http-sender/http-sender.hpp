#ifndef __http_sender_h__
#define __http_sender_h__
#include <WiFi.h>
#include <HTTPClient.h>
#include <vector>

class HttpSender
{
private:
    HTTPClient *client;
    WiFiClass *wifi;
    String host;
    uint16_t port;

public:
    HttpSender(WiFiClass *wifi, const char *ssid, const char *password, String host, uint16_t port = 80);
    ~HttpSender();
    void send(std::vector<uint8_t> &data);
};

#endif // __http_sender_h__

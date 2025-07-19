#include "http-sender.hpp"
#include <ArduinoJson.h>

HttpSender::HttpSender(WiFiClass *wifi, const char *ssid, const char *password, String host, uint16_t port)
{
    this->wifi = wifi;
    this->port = port;
    this->host = host;
    this->client = new HTTPClient();
    wifi->mode(WIFI_STA);
    wifi->begin(ssid, password);
    while (wifi->status() != WL_CONNECTED)
    {
        delay(50);
        USBSerial.println("Connecting to WiFi...");
    }
}

HttpSender::~HttpSender()
{
}

void HttpSender::send(std::vector<uint8_t> &data)
{
    String json;
    if (!data.empty())
    {
        ArduinoJson::JsonDocument doc;
        for (size_t i = 0; i < data.size(); ++i)
        {
            doc[i] = data[i];
        }
        serializeJson(doc, json);
    }
    else
    {
        json = "[]"; // Empty array if no data
    }
    this->client->begin(this->host, this->port, "/");
    this->client->addHeader("Content-Type", "application/json");
    this->client->addHeader("Content-Length", String(json.length()));
    auto code = this->client->POST(json);
    if (code != HTTP_CODE_OK)
    {
        USBSerial.printf("HTTP POST failed, code: %d\n", code);
    }
    else
    {
        USBSerial.println("Data sent successfully");
    }
}

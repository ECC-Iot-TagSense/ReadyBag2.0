#include "LineNotify.h"
#include <WiFiClientSecure.h> // WiFiClientSecure を使う

const char *host = "api.line.me";
const char token[] PROGMEM = "bIXCAB9vzbAsISLkF2wHvaPL8zVbyrDxDQ2h7e9F31TsEylm+8raEXL+OYvjo/g0IQ744c+HHs7S8rYY7yN3YiLjxJvLH7v08deqYMTY85Ni4HTriZLk8b2E4Urayei7DYkDgxjJt7TApwOCVOHhsAdB04t89/1O/w1cDnyilFU=";

void line_notify()
{
    WiFiClientSecure client; // Secure クライアントを使用
    client.setInsecure();    // 証明書の検証を無効化

    if (!client.connect(host, 443)) // HTTPS のポートで接続
    {
        Serial.println(F("Connection failed"));
        return;
    }

    // HTTPリクエストをフラッシュメモリから送信
    client.print(F(
        "POST /v2/bot/message/broadcast HTTP/1.1\r\n"
        "Host: api.line.me\r\n"
        "Authorization: Bearer "));
    client.print(token);
    client.print(F(
        "\r\nContent-Length: 53\r\n"
        "Content-Type: application/json\r\n\r\n"
        "{\"messages\":[{\"type\":\"text\",\"text\":\"忘れ物があります\"}]}"
        "\r\n"));

    // レスポンスの処理
    while (client.connected() || client.available())
    {
        if (client.available())
        {
            Serial.println(client.readStringUntil('\n'));
        }
    }
    client.stop();
}

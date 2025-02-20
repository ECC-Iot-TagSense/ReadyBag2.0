#include "connection.h"

const char *ssid = "hayato";
const char *password = "hayato222";

void WiFiConnect()
{
    WiFi.begin(ssid, password);
    unsigned long start = millis();
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(250);
        if (millis() - start > 10000)
        {
            return; // 10秒経過で接続失敗
        }
    }
    // 接続成功時はIPアドレス取得など必要に応じた処理を追加可能
}

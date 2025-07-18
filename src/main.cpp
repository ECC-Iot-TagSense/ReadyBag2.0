#include <SPIFFS.h>
#include <Arduino.h>
#include <M5Dial.h>
#include "encoder.h"
#include <vector>
#include "setting-screen.h"
#include "main-screen.h"
#include "reader.h"
#include "save-settings.h"
#include "settimer.h"
#include <Adafruit_NeoPixel.h>
#include "WiFi.h"
#include "http-sender.hpp"
#include "add-screen.hpp"
#include <map>
#include <tags.hpp>

#define LED_DATA_PIN 15
#define LED_LEN (5 * 3)

using std::vector;

const char *settingBasePath = "/settings";

#define SSID "maruyama"
#define PASSWORD "marufuck"
#define HOST "192.168.217.50"
#define PORT (8000)

Encoder *encoder;
std::vector<TagID> ids;
bool isFirst = true;
SettingState settingState;
Reader *reader;
ScreenState currentState = ScreenState::Main;
Adafruit_NeoPixel pixels(LED_LEN, LED_DATA_PIN);
HttpSender *sender;
vector<String> categories;
std::map<TagID, uint8_t> tags;
std::vector<uint8_t> existIds;

void setup()
{
    USBSerial.begin(115200);
    Serial2.begin(115200, SERIAL_8N1, 2, 1);
    M5Dial.begin(true);
    SPIFFS.begin(true);
    encoder = new Encoder(&M5Dial.Encoder);
    USBSerial.println("Start");
    settingState = readSetting(SPIFFS, settingBasePath);
    reader = new Reader(&Serial2);
    sender = new HttpSender(&WiFi, SSID, PASSWORD, HOST, PORT);
    tags = readTags(SPIFFS);
    pixels.fill(pixels.Color(255, 0, 0));
    pixels.show();
    reader->start();
    auto cat = {
        "サイフ",
        "名刺",
        "パスポート",
        "充電器",
        "常備薬"};
    for (const auto &c : cat)
    {
        categories.push_back(c);
    }
    sender->send(existIds); // 初期化時に空のデータを送信
}

void loop()
{
    M5Dial.update();
    encoder->update();
    USBSerial.println(">loop:0");
    USBSerial.printf(">diff: %d\n", encoder->difference());
    auto nextState = currentState;
    switch (currentState)
    {
    case ScreenState::Main:
        nextState = mainLoop(
            &M5Dial.Display,
            reader,
            encoder,
            &M5Dial.BtnA,
            settingState.scan,
            isFirst,
            settingState.light,
            tags,
            sender,
            &existIds,
            &pixels);

        break;

    case ScreenState::Setting:
        nextState = settingLoop(&M5Dial.Display, encoder, &M5Dial.BtnA, &settingState, isFirst);
        break;

    case ScreenState::Add:
        nextState = addLoop(
            SPIFFS,
            &M5Dial.Display,
            reader,
            encoder,
            &M5Dial.BtnA,
            isFirst,
            &tags,
            &categories);
        break;

    default:
        break;
    }
    if (currentState == ScreenState::Setting && nextState == ScreenState::Main)
    {
        saveSetting(SPIFFS, settingBasePath, settingState);
    }
    isFirst = nextState != currentState;
    currentState = nextState;
    delay(10);
}

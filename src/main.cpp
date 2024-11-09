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

#define LED_DATA_PIN 15
#define LED_LEN (5 * 3)

using std::vector;

const char *settingBasePath = "/settings";

Encoder *encoder;
std::vector<TagID> ids;
bool isFirst = true;
SettingState settingState;
Reader *reader;
ScreenState currentState = ScreenState::Main;
Adafruit_NeoPixel pixels(LED_LEN, LED_DATA_PIN);

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
    pixels.fill(pixels.Color(255, 0, 0));
    pixels.show();
}

void loop()
{
    M5Dial.update();
    encoder->update();
    auto nextState = currentState;
    switch (currentState)
    {
    case ScreenState::Main:
        nextState = mainLoop(&M5Dial.Display, reader, encoder, &M5Dial.BtnA, settingState.scan, isFirst, settingState.light, &ids, &pixels);
        break;

    case ScreenState::Setting:
        nextState = settingLoop(&M5Dial.Display, encoder, &M5Dial.BtnA, &settingState, isFirst);
        break;

    case ScreenState::Add:
        if (ids.size() > 0)
        {
            reader->stop();
            ids.clear();
            USBSerial.println("Tag Cleared");
        }
        else
        {
            reader->start();
            TagID tagId;
            std::get<0>(tagId) = 0x00;
            std::get<1>(tagId) = 0x11;
            std::get<2>(tagId) = 0x22;
            std::get<3>(tagId) = 0x33;
            std::get<4>(tagId) = 0x44;
            std::get<5>(tagId) = 0x55;
            std::get<6>(tagId) = 0x66;
            std::get<7>(tagId) = 0x77;
            std::get<8>(tagId) = 0x88;
            std::get<9>(tagId) = 0x99;
            std::get<10>(tagId) = 0xAA;
            std::get<11>(tagId) = 0xBB;
            ids.push_back(tagId);
            USBSerial.println("Tag Added");
        }
        nextState = ScreenState::Main;
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
}

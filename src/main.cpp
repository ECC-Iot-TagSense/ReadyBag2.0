#include <SPIFFS.h>
#include <Arduino.h>
#include <M5Dial.h>
#include "encoder.h"
#include <vector>
#include "setting-screen.h"
#include "main-screen.h"
#include "reader.h"
#include "save-settings.h"
#include <Adafruit_NeoPixel.h>

#define LED_DATA_PIN 15
#define LED_LEN (5 * 3)

using std::vector;

const char *settingBasePath = "/settings";

Encoder *encoder;
vector<uint16_t> ids;
bool isFirst = true;
SettingState settingState;
Reader *reader;
ScreenState currentState = ScreenState::Main;
Adafruit_NeoPixel pixels(LED_LEN, LED_DATA_PIN);

void setup()
{
    USBSerial.begin(115200);
    Serial.begin(115200);
    M5Dial.begin(true);
    SPIFFS.begin(true);
    encoder = new Encoder(&M5Dial.Encoder);
    USBSerial.println("Start");
    settingState = readSetting(SPIFFS, settingBasePath);
    reader = new Reader(&Serial);
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
        if (ids.size() > 1)
        {
            ids.clear();
        }
        else
        {
            ids.push_back(0x1234);
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

#ifndef __main_screen_h__
#define __main_screen_h__
#include "screen-state.h"
#include <SPIFFS.h>
#include <M5GFX.h>
#include "reader.h"
#include "encoder.h"
#include <utility/Button_Class.hpp>
#include <Adafruit_NeoPixel.h>

ScreenState mainLoop(
    M5GFX *display,
    Reader *reader,
    Encoder *encoder,
    m5::Button_Class *button,
    bool isScan,
    bool isFirst,
    bool enableLight,
    std::vector<TagID> *registeredIds,
    Adafruit_NeoPixel *pixels);
#endif

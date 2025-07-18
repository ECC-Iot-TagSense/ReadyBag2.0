#ifndef __add_screen_h__
#define __add_screen_h__
#include "screen-state.h"
#include <SPIFFS.h>
#include <M5GFX.h>
#include <reader.h>
#include <encoder.h>
#include <utility/Button_Class.hpp>
#include <map>

ScreenState addLoop(
    fs::FS &fs,
    M5GFX *display,
    Reader *reader,
    Encoder *encoder,
    m5::Button_Class *button,
    bool isFirst,
    std::map<TagID, uint8_t> *tags,
    std::vector<String> *category);

#endif // __add_screen_h__

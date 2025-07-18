#ifndef __add_screen_h__
#define __add_screen_h__
#include "screen-state.h"
#include <SPIFFS.h>
#include <M5GFX.h>
#include <reader.h>
#include <encoder.h>
#include <utility/Button_Class.hpp>

ScreenState addLoop(
    M5GFX *display,
    Reader *reader,
    Encoder *encoder,
    m5::Button_Class *button,
    bool isFirst,
    std::vector<TagID> *ids);

#endif // __add_screen_h__

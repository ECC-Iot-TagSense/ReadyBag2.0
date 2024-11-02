#ifndef __main_screen_h__
#define __main_screen_h__
#include "screen-state.h"
#include <M5GFX.h>
#include "reader.h"
#include "encoder.h"
#include <utility/Button_Class.hpp>

ScreenState mainLoop(M5GFX *display, Reader *reader, Encoder *encoder, m5::Button_Class button, bool isScan, std::vector<uint16_t> *registeredIds);

#endif

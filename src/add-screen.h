#include "screen.h"
#include "index.h"
#include "screen-state.h"
#include <M5GFX.h>
#include <encoder.h>
#include <utility/Button_Class.hpp>
#include "reader.h"

enum class AddState
{
    Select,
    Scan,
    Done,
};

ScreenState addLoop(M5GFX *display, Encoder *encoder, Reader *reader, m5::Button_Class *button, bool isFirst);

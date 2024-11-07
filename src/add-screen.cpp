#include "add-screen.h"
#include "index.h"
namespace AddScreen
{
    enum class State
    {
        Select,
        Scan,
        Done,
    };
    int waitTime = 0;
    State state = State::Select;
    int selectionIndex = 0;
} // namespace AddScreen
  //

ScreenState addLoop(M5GFX *display, Encoder *encoder, Reader *reader, m5::Button_Class *button, bool isFirst)
{
}

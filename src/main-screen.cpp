#include "main-screen.h"
#include "screen.h"
#include "index.h"
#include "reader.h"

namespace main_screen
{
    int selectionIndex = 0;
    const int selectionsMax = 2;
    MainSelection selections[selectionsMax + 1] = {MainSelection::Bell, MainSelection::Setting, MainSelection::Add};
    MainState previousState = MainState::NotScan;
}

ScreenState mainLoop(
    M5GFX *display,
    Reader *reader,
    Encoder *encoder,
    m5::Button_Class *button,
    bool isScan,
    bool isFirst,
    bool enableLight,
    std::map<TagID, uint8_t> &tags,
    HttpSender *sender,
    std::vector<uint8_t> *existIds,
    Adafruit_NeoPixel *pixels)
{
    using namespace main_screen;

    auto state = MainState::NotScan;
    auto nextScreenState = ScreenState::Main;
    if (isScan)
    {
        state = MainState::Nomal;
        auto currentExistTags = reader->read();
        auto currentExistIds = vector<uint8_t>();
        for (auto &tag : tags)
        {
            bool isExist = false;
            for (auto existId : currentExistTags)
            {
                if (tag.first == existId)
                {
                    currentExistIds.push_back(tag.second);
                    isExist = true;
                    break;
                }
            }

            if (!isExist)
            {
                state = MainState::Alert;
            }
        }
        auto isSameExistIds = false;
        if (currentExistIds.size() == existIds->size())
        {
            isSameExistIds = true;
            for (auto i = 0; i < currentExistIds.size(); i++)
            {
                if (currentExistIds[i] != existIds->at(i))
                {
                    isSameExistIds = false;
                    break;
                }
            }
        }
        if (!isSameExistIds)
        {
            USBSerial.println("Exist IDs changed, updating...");
            existIds->clear();
            for (auto &id : currentExistIds)
            {
                existIds->push_back(id);
            }
            sender->send(*existIds);
        }
    }
    if (state == MainState::Alert && enableLight)
    {
        pixels->fill(pixels->Color(255, 0, 0));
        pixels->show();
    }
    else
    {
        pixels->clear();
        pixels->show();
    }

    if (button->wasPressed())
    {
        auto currentSelection = selections[selectionIndex];
        switch (currentSelection)
        {
        case MainSelection::Bell:
            nextScreenState = ScreenState::Main;
            break;
        case MainSelection::Setting:
            nextScreenState = ScreenState::Setting;
            break;
        case MainSelection::Add:
            nextScreenState = ScreenState::Add;
            break;
        default:
            break;
        }
    }

    selectionIndex = updaterIndex(selectionIndex, selectionsMax, encoder->difference());
    if (!isFirst && encoder->difference() == 0 && state == previousState)
    {
        return nextScreenState;
    }
    if (isFirst)
    {
        selectionIndex = 0;
    }

    previousState = state;
    drawMainScreen(SPIFFS, display, state, selections[selectionIndex]);
    return nextScreenState;
}

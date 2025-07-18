#include "add-screen.hpp"
#include "screen.h"
#include "tags.hpp"

enum AddState
{
    SELECT_CATEGORY,
    SCANNING,
    COMPLETE,
    ERROR_DUBBING,
    ERROR_NOT_FOUND,
    MAIN
};

namespace add_screen
{
    bool forceUpdateScreen = false;
    AddState addState = SELECT_CATEGORY;
    int selectionIndex = 0;
    int waitCount = 0;
}

bool waiting(int &waitCount, int seconds)
{
    waitCount++;
    USBSerial.print(">waitCount:");
    USBSerial.println(waitCount);
    if (waitCount > seconds * 100) // seconds待つ
    {
        return true;
    }
    return false;
}

AddState selectCategory(
    fs::FS &fs,
    M5GFX *display,
    Encoder *encoder,
    m5::Button_Class *button,
    std::vector<String> *category,
    int &selectionIndex,
    bool isFirst)
{
    if (isFirst)
    {
        drawAddSelectorScreen(fs, display, category, selectionIndex);
        return AddState::SELECT_CATEGORY;
    }

    if (button->wasPressed())
    {
        return AddState::SCANNING;
    }

    if (encoder->difference() != 0)
    {
        selectionIndex += encoder->difference();
        if (selectionIndex < 0)
        {
            selectionIndex = category->size() - 1;
        }
        else if (selectionIndex >= category->size())
        {
            selectionIndex = 0;
        }
        drawAddSelectorScreen(fs, display, category, (uint8_t)selectionIndex);
    }
    return AddState::SELECT_CATEGORY;
}

AddState scanning(
    fs::FS &fs,
    M5GFX *display,
    Reader *reader,
    int &waitCount,
    bool isFirst,
    int selectionIndex,
    std::map<TagID, uint8_t> *tags)
{
    USBSerial.print(">scanIsFirst:");
    USBSerial.println(isFirst);
    if (isFirst)
    {
        drawAddMessageScreen(fs, display, AddMessage::Scanning);
        waitCount = 0;
        return AddState::SCANNING;
    }
    auto readedTags = reader->read();
    if (readedTags.empty())
    {
        auto ret = AddState::SCANNING;
        if (waiting(waitCount, 5)) // 5秒待つ
        {
            ret = AddState::ERROR_NOT_FOUND;
        }
        return ret;
    }
    if (readedTags.size() > 1)
    {
        return AddState::ERROR_DUBBING;
    }
    (*tags)[readedTags[0]] = (uint8_t)selectionIndex;
    writeTags(fs, *tags);
    auto a = readTags(fs);
    for (auto &tag : a)
    {
        USBSerial.printf("TagID: %016llx%08lx", std::get<0>(tag.first), std::get<1>(tag.first));
        USBSerial.printf(" Category: %d\n", tag.second);
    }

    return AddState::COMPLETE;
}

AddState message(
    fs::FS &fs,
    M5GFX *display,
    AddState state,
    bool isFirst,
    int &waitCount)
{
    if (isFirst)
    {
        waitCount = 0;
        switch (state)
        {
        case AddState::COMPLETE:
            drawAddMessageScreen(fs, display, AddMessage::Complete);
            USBSerial.println("Add complete");
            break;
        case AddState::ERROR_DUBBING:
            drawAddErrorScreen(fs, display, AddError::DoubleDetected);
            USBSerial.println("Add error: double detected");
            break;
        case AddState::ERROR_NOT_FOUND:
            drawAddErrorScreen(fs, display, AddError::NotFound);
            USBSerial.println("Add error: not found");
            break;
        default:
            return AddState::MAIN; // おかしいからmainに戻す
        }
    }
    if (waiting(waitCount, 3)) // 3秒待つ
    {
        return AddState::MAIN;
    }
    return state;
}

ScreenState addLoop(
    fs::FS &fs,
    M5GFX *display,
    Reader *reader,
    Encoder *encoder,
    m5::Button_Class *button,
    bool isFirst,
    std::map<TagID, uint8_t> *tags,
    std::vector<String> *category)
{
    using namespace add_screen;
    if (isFirst)
    {
        addState = SELECT_CATEGORY;
        selectionIndex = 0;
        forceUpdateScreen = true;
    }
    auto oldState = addState;
    switch (addState)
    {
    case SELECT_CATEGORY:
        addState = selectCategory(fs, display, encoder, button, category, selectionIndex, forceUpdateScreen);
        break;
    case SCANNING:
        addState = scanning(fs, display, reader, waitCount, forceUpdateScreen, selectionIndex, tags);
        break;
    case COMPLETE:
    case ERROR_DUBBING:
    case ERROR_NOT_FOUND:
        addState = message(fs, display, addState, forceUpdateScreen, waitCount);
        break;
    default:
        return ScreenState::Main;
    }
    forceUpdateScreen = oldState != addState;
    return ScreenState::Add;
}

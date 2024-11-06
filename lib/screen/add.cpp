#include "add.h"
#include "colors.h"
#include "draw.h"

void drawAddSelectorScreen(fs::FS &fs, M5GFX *display, vector<String> *category, int selectionIndex)
{
    uint32_t selectColor = 0xFFFFFF;
    uint32_t previewColor = 0xC7C7C7;
    M5Canvas canvas(display);
    canvas.createSprite(display->width(), display->height());
    canvas.fillSprite(BACKGROUND_COLOR);
    betterDrawPngFile(&canvas, fs, "/status-set.png", initCoordinate(0, 0), datum_t::top_center);
    betterDrawPngFile(&canvas, fs, "/add-state.png", initCoordinate(0, 22), datum_t::top_center);

    canvas.setTextFont(0);
    canvas.setTextSize(1);
    canvas.setFont(&fonts::lgfxJapanGothic_16);
    canvas.setTextColor(previewColor);
    auto middle = display->width() / 2;

    auto previousIndex = selectionIndex - 1;
    if (previousIndex < 0)
    {
        previousIndex = category->size() - 1;
    }
    canvas.setTextDatum(datum_t::top_center);
    canvas.drawString((*category)[previousIndex], middle, 105);

    auto nextIndex = selectionIndex + 1;
    if (nextIndex >= category->size())
    {
        nextIndex = 0;
    }
    canvas.setTextDatum(datum_t::top_center);
    auto nextText = (*category)[nextIndex];

    canvas.drawString(nextText, middle, 173);

    auto currentText = (*category)[selectionIndex];
    auto currentTextY = 136;
    canvas.setTextColor(selectColor);
    canvas.setFont(&fonts::lgfxJapanGothic_20);
    canvas.setTextDatum(datum_t::top_center);
    canvas.drawString(currentText, middle, currentTextY);

    auto textWidth = canvas.textWidth(currentText, &fonts::lgfxJapanGothic_20);
    auto textHeight = canvas.fontHeight(&fonts::lgfxJapanGothic_20);
    auto markerX = (textWidth / 2) + 16;
    auto makerY = currentTextY + (textHeight / 2) - 4;

    betterDrawPngFile(&canvas, fs, "/add-s-R.png", initCoordinate(markerX, makerY), datum_t::top_center);
    betterDrawPngFile(&canvas, fs, "/add-s-L.png", initCoordinate(-markerX, makerY), datum_t::top_center);

    display->startWrite();
    canvas.pushSprite(0, 0);
    display->endWrite();
}

void drawAddMessageScreen(fs::FS &fs, M5GFX *display, AddMessage message)
{
    M5Canvas canvas(display);
    canvas.createSprite(display->width(), display->height());
    canvas.fillSprite(BACKGROUND_COLOR);
    betterDrawPngFile(&canvas, fs, "/status-set.png", initCoordinate(0, 0), datum_t::top_center);
    betterDrawPngFile(&canvas, fs, "/add-state.png", initCoordinate(0, 22), datum_t::top_center);

    switch (message)
    {
    case AddMessage::Scanning:
        betterDrawPngFile(&canvas, fs, "/add-scan.png", initCoordinate(0, 120), datum_t::top_center);
        break;

    case AddMessage::Complete:
        betterDrawPngFile(&canvas, fs, "/add-complete.png", initCoordinate(0, 120), datum_t::top_center);

    default:
        break;
    }

    display->startWrite();
    canvas.pushSprite(0, 0);
    display->endWrite();
}

void drawAddErrorScreen(fs::FS &fs, M5GFX *display, String message)
{
    M5Canvas canvas(display);
    canvas.createSprite(display->width(), display->height());
    canvas.fillSprite(BACKGROUND_COLOR);
    betterDrawPngFile(&canvas, fs, "/status-set.png", initCoordinate(0, 0), datum_t::top_center);
    betterDrawPngFile(&canvas, fs, "/add-state.png", initCoordinate(0, 22), datum_t::top_center);

    display->startWrite();
    canvas.pushSprite(0, 0);
    display->endWrite();
}

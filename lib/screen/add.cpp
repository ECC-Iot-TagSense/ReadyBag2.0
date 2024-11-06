#include "add.h"
#include "colors.h"
#include "draw.h"

void drawAddScreen(fs::FS &fs, M5GFX *display, AddsState state, vector<String> *category, int selectionIndex)
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
    if (selectionIndex > 0)
    {
        canvas.setTextDatum(datum_t::top_center);
        auto index = selectionIndex - 1;
        canvas.setCursor(display->width() / 2, 105);
        canvas.print((*category)[index]);
    }

    if (selectionIndex < category->size() - 1)
    {
        canvas.setTextDatum(datum_t::top_center);
        auto index = selectionIndex + 1;
        canvas.setCursor(0, 173);
        canvas.print((*category)[index]);
    }

    canvas.setTextColor(selectColor);
    // canvas.setTextSize(20);
    canvas.setFont(&fonts::lgfxJapanGothic_20);
    canvas.setTextDatum(datum_t::top_center);
    canvas.setCursor(0, 136);
    canvas.print((*category)[selectionIndex]);

    display->startWrite();
    canvas.pushSprite(0, 0);
    display->endWrite();
}

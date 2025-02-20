#include "main.h"
#include "colors.h"
#include "draw.h"

void drawMainScreen(fs::FS &fs, M5GFX *display, MainState state, MainSelection selection)
{
    auto canvas = M5Canvas(display);
    canvas.createSprite(display->width(), display->height());
    canvas.fillSprite(BACKGROUND_COLOR);
    betterDrawPngFile(&canvas, fs, "/line.png", initCoordinate(0, 0), datum_t::top_center);

    switch (state)
    {
    case MainState::Nomal:
        betterDrawPngFile(&canvas, fs, "/status-nomal.png", initCoordinate(0, 0), datum_t::top_center);
        break;

    case MainState::Alert:
        betterDrawPngFile(&canvas, fs, "/status-alert.png", initCoordinate(0, 0), datum_t::top_center);
        break;

    case MainState::NotScan:
        betterDrawPngFile(&canvas, fs, "/status-scan-off.png", initCoordinate(0, 0), datum_t::top_center);
        break;
    default:
        break;
    }

    betterDrawPngFile(&canvas, fs, "/add.png", initCoordinate(38, 96), datum_t::top_left);
    betterDrawPngFile(&canvas, fs, "/setting.png", initCoordinate(-40, 98), datum_t::top_right);

    auto bellCoordinate = initCoordinate(0, 23);
    switch (selection)
    {
    case MainSelection::Bell:
        USBSerial.println("MainSelection::Bell");
        betterDrawPngFile(&canvas, fs, "/bell-sel.png", bellCoordinate, datum_t::top_center);
        betterDrawPngFile(&canvas, fs, "/active-effect-up.png", initCoordinate(0, 11), datum_t::top_center);
        break;
    case MainSelection::Add:
        USBSerial.println("MainSelection::Add");
        betterDrawPngFile(&canvas, fs, "/active-effect-L-white.png", initCoordinate(20, 78), datum_t::top_left);
        break;
    case MainSelection::Setting:

        USBSerial.println("MainSelection::Setting");
        betterDrawPngFile(&canvas, fs, "/active-effect-R-white.png", initCoordinate(-16, 76), datum_t::top_right);
        break;
    }
    if (selection != MainSelection::Bell)
    {
        betterDrawPngFile(&canvas, fs, "/bell.png", bellCoordinate, datum_t::top_center);
    }

    display->startWrite();
    canvas.pushSprite(0, 0);
    display->endWrite();
}

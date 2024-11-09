#include "main.h"
#include "colors.h"
#include "draw.h"
#include "settimer.h"


void drawSetTimeScreen(fs::FS &fs, M5GFX *display, SetTimeSelection state, Time time)

{
    auto canvas = M5Canvas(display);
    canvas.createSprite(display->width(), display->height());
    canvas.fillSprite(BACKGROUND_COLOR);

    auto bellCoordinate = initCoordinate(0, 23);

    betterDrawPngFile(&canvas, fs, "/status-set.png", initCoordinate(0, 0), datum_t::top_center);
    betterDrawPngFile(&canvas, fs, "/set-user-clock.png", bellCoordinate, datum_t::top_center);

    switch (state)
    {
    case SetTimeSelection::HoursTens:
        betterDrawPngFile(&canvas, fs, "/time-selecter_L.png", initCoordinate(68, 98), datum_t::top_left);
        break;

    case SetTimeSelection::HoursUnits:
        betterDrawPngFile(&canvas, fs, "/time-selecter_L.png", initCoordinate(91, 98), datum_t::top_left);
        break;

    case SetTimeSelection::MinutesTens:
        betterDrawPngFile(&canvas, fs, "/time-selecter_L.png", initCoordinate(137, 98), datum_t::top_left);
        break;

    case SetTimeSelection::MinutesUnits:
        betterDrawPngFile(&canvas, fs, "/time-selecter_L.png", initCoordinate(1600, 98), datum_t::top_left);
        break;
    }

    timerset(canvas, fs, time.hours/10,initCoordinate(66, 116) , datum_t::top_center);
    timerset(canvas, fs, time.hours%10,initCoordinate(88, 116) , datum_t::top_center);
    timerset(canvas, fs, time.minutes/10,initCoordinate(133, 116) , datum_t::top_center);
    timerset(canvas, fs, time.minutes%10,initCoordinate(155, 116) , datum_t::top_center);
    betterDrawPngFile(&canvas, fs, "/font/36p/colon.png", initCoordinate(110, 116), datum_t::top_left);



    display->startWrite();
    canvas.pushSprite(0, 0);
    display->endWrite();
}

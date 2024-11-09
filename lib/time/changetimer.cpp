#include "main.h"
#include "colors.h"
#include "draw.h"
#include "changetimer.h"

void drawSetTimeScreen(fs::FS &fs, M5GFX *display, ChangeTimeSelection state, Time time, bool isUp)
{
    auto canvas = M5Canvas(display);
    canvas.createSprite(display->width(), display->height());
    canvas.fillSprite(BACKGROUND_COLOR);

    auto bellCoordinate = initCoordinate(0, 23);

    betterDrawPngFile(&canvas, fs, "/status-set.png", initCoordinate(0, 0), datum_t::top_center);
    betterDrawPngFile(&canvas, fs, "/set-alarm-time.png", bellCoordinate, datum_t::top_center);

    int selectUP = 80;
    int selectDOWN = 152;

    int selectY ;
    if (isUp)
    {
        selectY = selectUP;
    }else
    {
        selectY = selectDOWN;
    }
    

    switch (state)
    {
    case ChangeTimeSelection::HoursTens:
        betterDrawPngFile(&canvas, fs, "/time-selecter_S.png", initCoordinate(74, selectY), datum_t::top_left);
        break;

    case ChangeTimeSelection::HoursUnits:
        betterDrawPngFile(&canvas, fs, "/time-selecter_S.png", initCoordinate(94, selectY), datum_t::top_left);
        break;

    case ChangeTimeSelection::MinutesTens:
        betterDrawPngFile(&canvas, fs, "/time-selecter_S.png", initCoordinate(125, selectY), datum_t::top_left);
        break;

    case ChangeTimeSelection::MinutesUnits:
        betterDrawPngFile(&canvas, fs, "/time-selecter_S.png", initCoordinate(147, selectY), datum_t::top_left);
        break;

    default:
        break;
    }

    timerchange(canvas, fs, time.hours / 10, initCoordinate(73, 93), datum_t::top_center);
    timerchange(canvas, fs, time.hours % 10, initCoordinate(93, 93), datum_t::top_center);
    timerchange(canvas, fs, time.minutes / 10, initCoordinate(133, 93), datum_t::top_center);
    timerchange(canvas, fs, time.minutes % 10, initCoordinate(153, 93), datum_t::top_center);
    timerchange(canvas, fs, time.hours / 10, initCoordinate(73, 165), datum_t::top_center);
    timerchange(canvas, fs, time.hours % 10, initCoordinate(93, 165), datum_t::top_center);
    timerchange(canvas, fs, time.minutes / 10, initCoordinate(133, 165), datum_t::top_center);
    timerchange(canvas, fs, time.minutes % 10, initCoordinate(153, 165), datum_t::top_center);
    betterDrawPngFile(&canvas, fs, "/font/32p/colon.png", initCoordinate(113, 93), datum_t::top_left);
    betterDrawPngFile(&canvas, fs, "/font/32p/colon.png", initCoordinate(113, 165), datum_t::top_left);
    betterDrawPngFile(&canvas, fs, "/font/32p/row.png", initCoordinate(110, 165), datum_t::top_left);


    display->startWrite();
    canvas.pushSprite(0, 0);
    display->endWrite();
}

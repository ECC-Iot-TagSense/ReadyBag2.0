#include "setting.h"
#include "colors.h"
#include "draw.h"

void drawSettingIcon(bool is_active, M5Canvas *canvas, fs::FS &fs, Coordinate_t coordinate, datum_t datum)
{
    if (is_active)
    {
        betterDrawPngFile(canvas, fs, "/set-icon-active.png", coordinate, datum);
    }
    else
    {
        betterDrawPngFile(canvas, fs, "/set-icon-inactive.png", coordinate, datum);
    }
}

SettingState initSettingState(bool light, bool scan, bool alert_time, bool user_clock)
{
    return SettingState({light, scan, alert_time, user_clock});
}

void drawSettingScreen(fs::FS &fs, M5GFX *display, SettingState state, SettingSelection selection)
{
    auto canvas = M5Canvas(display);
    canvas.createSprite(display->width(), display->height());
    canvas.fillSprite(BACKGROUND_COLOR);
    betterDrawPngFile(&canvas, fs, "/line.png", initCoordinate(0, 0), datum_t::top_center);
    betterDrawPngFile(&canvas, fs, "/status-set.png", initCoordinate(0, 0), datum_t::top_center);

    drawSettingIcon(state.light, &canvas, fs, initCoordinate(31, 74), datum_t::top_left);
    drawSettingIcon(state.scan, &canvas, fs, initCoordinate(31, 153), datum_t::top_left);
    drawSettingIcon(state.alert_time, &canvas, fs, initCoordinate(-31, 74), datum_t::top_right);
    drawSettingIcon(state.user_clock, &canvas, fs, initCoordinate(-31, 153), datum_t::top_right);

    betterDrawPngFile(&canvas, fs, "/back-icon.png", initCoordinate(80, 28), datum_t::top_left);
    betterDrawPngFile(&canvas, fs, "/set-icon.png", initCoordinate(0, 18), datum_t::top_center);

    if (selection == SettingSelection::Back)
    {
        betterDrawPngFile(&canvas, fs, "/active-effect-L-white.png", initCoordinate(56, 10), datum_t::top_left);
    }

    auto lightIconCoordinate = initCoordinate(53, 92);
    if (selection == SettingSelection::Light)
    {
        betterDrawPngFile(&canvas, fs, "/active-effect-L-orange.png", initCoordinate(19, 63), datum_t::top_left);
        betterDrawPngFile(&canvas, fs, "/set-led-sel.png", lightIconCoordinate, datum_t::top_left);
    }
    else
    {
        betterDrawPngFile(&canvas, fs, "/set-led.png", lightIconCoordinate, datum_t::top_left);
    }

    auto scanIconCoordinate = initCoordinate(58, 174);
    if (selection == SettingSelection::Scan)
    {
        betterDrawPngFile(&canvas, fs, "/active-effect-L-orange.png", initCoordinate(19, 142), datum_t::top_left);
        betterDrawPngFile(&canvas, fs, "/set-scan-sel.png", scanIconCoordinate, datum_t::top_left);
    }
    else
    {
        betterDrawPngFile(&canvas, fs, "/set-scan.png", scanIconCoordinate, datum_t::top_left);
    }

    auto alertTimeIconCoordinate = initCoordinate(-54, 94);
    if (selection == SettingSelection::AlertTime)
    {
        betterDrawPngFile(&canvas, fs, "/active-effect-R-orange.png", initCoordinate(-17, 63), datum_t::top_right);
        betterDrawPngFile(&canvas, fs, "/set-alert-time-sel.png", alertTimeIconCoordinate, datum_t::top_right);
    }
    else
    {
        betterDrawPngFile(&canvas, fs, "/set-alert-time.png", alertTimeIconCoordinate, datum_t::top_right);
    }

    auto userClockIconCoordinate = initCoordinate(-54, 174);
    if (selection == SettingSelection::UserClock)
    {
        betterDrawPngFile(&canvas, fs, "/active-effect-R-orange.png", initCoordinate(-17, 142), datum_t::top_right);
        betterDrawPngFile(&canvas, fs, "/set-user-clock-sel.png", userClockIconCoordinate, datum_t::top_right);
    }
    else
    {
        betterDrawPngFile(&canvas, fs, "/set-user-clock.png", userClockIconCoordinate, datum_t::top_right);
    }
    display->startWrite();
    canvas.pushSprite(0, 0);
    display->endWrite();
}

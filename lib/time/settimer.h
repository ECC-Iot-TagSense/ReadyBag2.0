#ifndef __SCREEN_SETTIMER_H__
#define __SCREEN_SETTIMER_H__
#include <SPIFFS.h>
#include <M5GFX.h>
#include <FS.h>
#include <timetime.h>

enum class SetTimeSelection {
    HoursTens,   // 時間の十の位
    HoursUnits,  // 時間の一の位    
    MinutesTens, // 分の十の位
    MinutesUnits, // 分の一の位
};



void drawSetTimeScreen(fs::FS &fs, M5GFX *display, SetTimeSelection state,Time time);

#endif
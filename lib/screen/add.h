#ifndef __screen_add_h__
#define __screen_add_h__
#include <SPIFFS.h>
#include <M5GFX.h>
#include <Arduino.h>
#include <FS.h>
#include <vector>

using std::vector;

enum class AddsState
{
    Select,
    Wait,
    Done,
};

void drawAddScreen(fs::FS &fs, M5GFX *display, AddsState state, vector<String> *category, int selectionIndex);

#endif

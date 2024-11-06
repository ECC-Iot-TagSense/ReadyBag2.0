#ifndef __screen_add_h__
#define __screen_add_h__
#include <SPIFFS.h>
#include <M5GFX.h>
#include <Arduino.h>
#include <FS.h>
#include <vector>

using std::vector;

enum class AddMessage
{
    Scanning,
    Complete,
};

void drawAddSelectorScreen(fs::FS &fs, M5GFX *display, vector<String> *category, int selectionIndex);
void drawAddMessageScreen(fs::FS &fs, M5GFX *display, AddMessage message);
void drawAddErrorScreen(fs::FS &fs, M5GFX *display, String message);

#endif

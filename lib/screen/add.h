#ifndef __screen_add_h__
#define __screen_add_h__
#include <SPIFFS.h>
#include <M5GFX.h>
#include <Arduino.h>
#include <FS.h>
#include <vector>

using std::vector;

void drawAddSelectorScreen(fs::FS &fs, M5GFX *display, vector<String> *category, int selectionIndex);
void drawAddWaitScreen(fs::FS &fs, M5GFX *display);
void drawAddCompleteScreen(fs::FS &fs, M5GFX *display);

#endif

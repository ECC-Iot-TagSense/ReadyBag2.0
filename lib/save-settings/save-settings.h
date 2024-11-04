#include <FS.h>
#include <setting.h>
#include <ArduinoJson.hpp>

SettingState readSetting(fs::FS &fs, const char *basePath);
void saveSetting(fs::FS &fs, const char *basePath, SettingState state);

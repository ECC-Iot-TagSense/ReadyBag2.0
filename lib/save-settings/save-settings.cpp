#include "save-settings.h"
#include <StreamUtils.h>
#include <Arduino.h>

const char *defaultPath = "default.json";
const char *userPath = "user.json";

SettingState readSetting(fs::FS &fs, const char *basePath)
{
    char settingPath[32];
    sprintf(settingPath, "%s/%s", basePath, userPath);
    if (!fs.exists(settingPath))
    {
        sprintf(settingPath, "%s/%s", basePath, defaultPath);
    }

    auto file = fs.open(settingPath, "r");
    ReadBufferingStream bufferedFile{file, 64};
    ArduinoJson::JsonDocument doc;
    ArduinoJson::deserializeJson(doc, bufferedFile);
    bool light = doc["light"];
    bool scan = doc["scan"];
    bool alertTime = doc["alertTime"];
    bool userClock = doc["userClock"];
    file.close();
    return initSettingState(light, scan, alertTime, userClock);
}

void saveSetting(fs::FS &fs, const char *basePath, SettingState state)
{
    char settingPath[32];
    sprintf(settingPath, "%s/%s", basePath, userPath);
    auto file = fs.open(settingPath, "w");
    ArduinoJson::JsonDocument doc;
    doc["light"] = state.light;
    doc["scan"] = state.scan;
    doc["alertTime"] = state.alert_time;
    doc["userClock"] = state.user_clock;
    ArduinoJson::serializeJson(doc, file);
    file.close();
}

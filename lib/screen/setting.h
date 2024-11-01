#ifndef __SCREEN_SETTING_H__
#define __SCREEN_SETTING_H__
#include <SPIFFS.h>
#include <M5GFX.h>
#include <FS.h>

// 設定の状態trueだと緑falseだと赤
// auto state = initSettingState(true, false, true, false);
// ↑こんなかんじ
struct SettingState
{
    bool light;
    bool scan;
    bool alert_time;
    bool user_clock;
};

// どれが選択されているか
// SettingSelection::Light などで指定
// auto {変数名} = SettingSelection::Light;
// ↑こんなんじでいける
enum SettingSelection
{
    Light,
    Scan,
    AlertTime,
    UserClock,
    Back,
};

// SettingStateの初期化関数
SettingState initSettingState(bool light, bool scan, bool alert_time, bool user_clock);

// 設定画面を描画するやつ
// 使い方はmain画面と同じ
void drawSettingScreen(fs::FS &fs, M5GFX *display, SettingState state, SettingSelection selection);
#endif

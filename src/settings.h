#ifndef IMAGE_DISPLAY_H
#define IMAGE_DISPLAY_H

#include <M5GFX.h>
#include <FS.h>

// 設定の状態判定用の変数
struct SettingState
{
    bool light;
    bool scan;
    bool alert_time;
    bool user_clock;
};

#endif // IMAGE_DISPLAY_H

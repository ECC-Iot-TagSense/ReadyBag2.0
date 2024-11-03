#include "setting-screen.h"
#include "screen.h"
#include "index.h"

namespace setting_screen
{
    int selectionIndex = 0;
    const int selectionsMax = 4;
    SettingSelection selections[selectionsMax + 1] = {SettingSelection::Back, SettingSelection::Light, SettingSelection::Scan, SettingSelection::AlertTime, SettingSelection::UserClock};
}

ScreenState settingLoop(M5GFX *display, Encoder *encoder, m5::Button_Class *button, SettingState *setistate, bool isFirst)
{
    using namespace setting_screen;

    ScreenState nextScreenState = ScreenState::Setting; // 初期状態を設定
    auto wasPressed = button->wasPressed();

    if (wasPressed)
    {
        auto currentSelection = selections[selectionIndex];
        switch (currentSelection)
        {
        case SettingSelection::Back:
            nextScreenState = ScreenState::Main;
            break;
        case SettingSelection::Light:
            // ライトの設定の変更の処理
            setistate->light = !setistate->light;
            break;
        case SettingSelection::Scan:
            // スキャン設定の変更の処理
            setistate->scan = !setistate->scan;
            break;
        case SettingSelection::AlertTime:
            // アラートの設定の変更の処理
            setistate->alert_time = !setistate->alert_time;
            break;
        case SettingSelection::UserClock:
            // 時計の設定の変更の処理
            setistate->user_clock = !setistate->user_clock;
            break;
        default:
            break;
        }
    }

    if (!isFirst && encoder->difference() == 0 && !wasPressed)
    {
        return nextScreenState;
    }
    selectionIndex = updaterIndex(selectionIndex, selectionsMax, encoder->difference()); // 選択肢の変更
    if (isFirst)
    {
        selectionIndex = 0;
    }
    drawSettingScreen(SPIFFS, display, *setistate, selections[selectionIndex]); // 画面描画
    return nextScreenState;                                                     // 次の画面を返す
}

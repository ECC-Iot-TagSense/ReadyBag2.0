#ifndef __setting_screen_h__
#define __setting_screen_h__

#include "screen-state.h"           // スクリーン状態を定義するヘッダーファイル
#include <SPIFFS.h>                 // SPIFFS用のライブラリ
#include <M5GFX.h>                  // M5Stack用のグラフィックスライブラリ
#include "encoder.h"                // エンコーダー操作を持つクラスのヘッダーファイル
#include <utility/Button_Class.hpp> // ボタン操作のためのクラス
#include "screen.h"                 // タイトル画面のメインループ処理を行う関数のプロトタイプ

// 設定画面のメインループ処理を行う関数のプロトタイプ
ScreenState settingLoop(M5GFX *display, Encoder *encoder, m5::Button_Class *button, SettingState *setistate, bool isFirst);

#endif

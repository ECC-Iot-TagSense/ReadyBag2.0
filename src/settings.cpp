#include <M5Dial.h>  // M5Stack ライブラリ
#include <SD.h>     // SDカード用のライブラリ

#include "settings.h"

// 現在選択されている画像のID
ImageID selectedImage = ADD;

// 画像を表示する関数
void displayImageFromDataFolder(ImageID imageId) {
    switch (imageId) {
        case ADD:
            M5.Lcd.drawJpgFile(SD, "/data/add.png");
            break;
        case BELL:
            M5.Lcd.drawJpgFile(SD, "/data/bell.png");
            break;
        case SETTING:
            M5.Lcd.drawJpgFile(SD, "/data/setting.png");
            break;
        case STATUS_ALERT:
            M5.Lcd.drawJpgFile(SD, "/data/status-alert.png");
            break;
        case STATUS_NORMAL:
            M5.Lcd.drawJpgFile(SD, "/data/status-normal.png");
            break;
        case STATUS_SCAN_OFF:
            M5.Lcd.drawJpgFile(SD, "/data/status-scan-off.png");
            break;
    }
}

// 回転率に基づいて画像を変更する関数
void updateImageBasedOnRotation(int rotationRate) {
    if (rotationRate > 0) {
        // 右回転で次の画像
        selectedImage = (selectedImage == STATUS_SCAN_OFF) ? ADD : static_cast<ImageID>(selectedImage + 1);
    } else if (rotationRate < 0) {
        // 左回転で前の画像
        selectedImage = (selectedImage == ADD) ? STATUS_SCAN_OFF : static_cast<ImageID>(selectedImage - 1);
    }
    // 画像を表示
    displayImageFromDataFolder(selectedImage);
}

// SDカードを初期化する関数
void initializeSDCard() {
    if (!SD.begin()) {
        Serial.println("SDカードの初期化に失敗しました");
    }
}

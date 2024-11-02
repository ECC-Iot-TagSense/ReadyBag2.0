#ifndef IMAGE_DISPLAY_H
#define IMAGE_DISPLAY_H

#include <M5GFX.h>
#include <FS.h>

// 画像IDを定義
enum ImageID {
    ADD,
    BELL,
    SETTING,
    STATUS_ALERT,
    STATUS_NORMAL,
    STATUS_SCAN_OFF
};

// 関数のプロトタイプ
void displayImageFromDataFolder(ImageID imageId);
void updateImageBasedOnRotation(int rotationRate);
void initializeSDCard();

#endif // IMAGE_DISPLAY_H

#ifndef __READER_H__
#define __READER_H__
#include <Arduino.h>
#include <vector>
#include <tuple>

// using TagID = std::tuple<uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t>;

// 　12byteのタグID
using TagID = std::tuple<uint64_t, uint32_t>;

class Reader
{
private:
    HardwareSerial *serial;
    std::vector<TagID> tagIds;
    std::vector<TagID> readTagIds;
    uint8_t *buf;
    int bufSize;
    portMUX_TYPE readMux = portMUX_INITIALIZER_UNLOCKED;
    portMUX_TYPE idsMux = portMUX_INITIALIZER_UNLOCKED;

public:
    Reader(HardwareSerial *serial);
    ~Reader();

    void start();              // 読み取り開始
    void stop();               // 読み取り停止
    std::vector<TagID> read(); // 最新のデータを読み取る
    void update();
};

#endif

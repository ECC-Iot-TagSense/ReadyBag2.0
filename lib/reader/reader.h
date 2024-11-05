#ifndef __READER_H__
#define __READER_H__
#include <Arduino.h>
#include <vector>
#include <tuple>

//　12byteのタグID
using TagID = std::tuple<uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t>;

class Reader
{
private:
    HardwareSerial *serial;
    std::vector<TagID> tagIds;
    TagID tagId;
    char piece;

public:
    Reader(HardwareSerial *serial);
    ~Reader();

    void start();              // 読み取り開始
    void stop();               // 読み取り停止
    std::vector<TagID> read(); // 最新のデータを読み取る
};

#endif
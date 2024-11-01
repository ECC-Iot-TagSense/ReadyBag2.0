#ifndef __READER_H__
#define __READER_H__
#include <Arduino.h>
#include <vector>

class Reader
{
private:
    HardwareSerial serial;

public:
    Reader(HardwareSerial serial);
    ~Reader();

    void start();                 // 読み取り開始
    std::vector<uint16_t> read(); // 最新のデータを読み取る
};

#endif

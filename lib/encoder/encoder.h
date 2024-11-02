#ifndef __ENCODER_H__
#define __ENCODER_H__
#include <utility/Encoder.h>

class Encoder
{
private:
    ENCODER *encoder;
    int32_t lastValue = 0;
    int32_t value = 0;

public:
    Encoder(ENCODER *encoder);
    ~Encoder();

    int32_t difference(); // 前回の値からの差分を返す
    void update();        // 値を更新する
};
#endif

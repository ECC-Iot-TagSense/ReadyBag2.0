#include "encoder.h"

Encoder::Encoder(ENCODER *encoder)
{
    this->encoder = encoder;
}

Encoder::~Encoder()
{
}

int Encoder::difference()
{
    return this->value - this->lastValue;
}

void Encoder::update()
{
    auto value = this->encoder->read();
    if (abs(this->lastValue * 4 - value) < 4 && this->value == this->lastValue)
    {
        return;
    }
    this->lastValue = this->value;
    this->value = value / 4;
}

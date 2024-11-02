#include "reader.h"

Reader::Reader(HardwareSerial *serial)
{
    this->serial = serial;
}

Reader::~Reader()
{
}

void Reader::start()
{
}

std::vector<uint16_t> Reader::read()
{
    return std::vector<uint16_t>();
}

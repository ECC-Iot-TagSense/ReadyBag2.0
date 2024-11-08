#include "reader.h"

#define SLIP_END 0xC0
#define SLIP_ESC 0xDB
#define SLIP_ESC_END 0xDC
#define SLIP_ESC_ESC 0xDD

void UpdateTask(void *arg)
{
    Reader *reader = (Reader *)arg;
    while (true)
    {
        reader->update();
        delayMicroseconds(1);
    }
}

Reader::Reader(HardwareSerial *serial)
{
    this->serial = serial;
    this->buf = new uint8_t[12];
    this->bufSize = 0;
}

Reader::~Reader()
{
}

void Reader::start()
{
    xTaskCreatePinnedToCore(UpdateTask, "UpdateTask", 4096, this, 1, NULL, 1);
}

void Reader::stop()
{
}

std::vector<TagID> Reader::read()
{ // 最新のデータを読み取る
    std::vector<TagID> retTagIds(this->tagIds.size());
    portENTER_CRITICAL_ISR(&this->idsMux);
    std::copy(this->tagIds.begin(), this->tagIds.end(), retTagIds.begin());
    portEXIT_CRITICAL_ISR(&this->idsMux);
    return retTagIds;
}

void Reader::update()
{
    bool isBreak = false;
    bool isEsc = false;
    if (!this->serial->available())
    {
        return;
    }
    uint8_t *readData = new uint8_t[128];
    auto read = this->serial->readBytes(readData, 128);

    for (int i = 0; i < read; i++)
    {
        auto data = readData[i];
        if (data == SLIP_ESC)
        {
            isEsc = true;
            continue;
        }
        if (isEsc)
        {
            isEsc = false;
            if (data == SLIP_ESC_END)
            {
                data = SLIP_END;
            }
            else if (data == SLIP_ESC_ESC)
            {
                data = SLIP_ESC;
            }
        }
        if (data == SLIP_END)
        {
            isBreak = true;
            this->bufSize = 0;
            break;
        }
        this->buf[this->bufSize++] = data;
        if (this->bufSize >= 12)
        {
            uint64_t id1;
            uint32_t id2;
            memcpy(&id1, this->buf, sizeof(uint64_t));
            memcpy(&id2, this->buf + sizeof(uint64_t), sizeof(uint32_t));
            TagID tagId = std::make_tuple(id1, id2);
            Serial.print(id1, HEX);
            Serial.println(id2, HEX);
            portENTER_CRITICAL_ISR(&this->readMux);
            if (std::count(this->readTagIds.begin(), this->readTagIds.end(), tagId) == 0)
            {
                this->readTagIds.push_back(tagId);
            }
            portEXIT_CRITICAL_ISR(&this->readMux);
            this->bufSize = 0;
        }
    }
    if (!isBreak)
    {
        return;
    }

    portENTER_CRITICAL_ISR(&this->idsMux);
    this->tagIds.clear();
    portENTER_CRITICAL_ISR(&this->readMux);
    for (auto tagId : this->readTagIds)
    {
        this->tagIds.push_back(tagId);
    }
    portEXIT_CRITICAL_ISR(&this->idsMux);
    this->readTagIds.clear();
    portEXIT_CRITICAL_ISR(&this->readMux);
}

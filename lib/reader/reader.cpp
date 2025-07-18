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
        delay(1);
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
    std::copy(this->tagIds.begin(), this->tagIds.end(), retTagIds.begin());
    return retTagIds;
}

void Reader::update()
{
    bool isEnd = false;
    bool isEsc = false;
    if (!this->serial->available())
    {
        return;
    }
    // auto read = this->serial->readBytesUntil(readData, 128);

    // for (int i = 0; i < read; i++)
    while (this->serial->available())
    {

        auto data = this->serial->read();
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
            isEnd = true;
            this->bufSize = 0;
            break;
        }
        if (this->bufSize >= 12)
        {
            USBSerial.println("Buffer overflow, resetting buffer");
            this->bufSize = 0; // Reset buffer if overflow
        }
        this->buf[this->bufSize++] = data;
        if (this->bufSize >= 12)
        {
            // USBSerial.println("Buffer full, processing tag ID");
            uint64_t id1;
            uint32_t id2;
            memcpy(&id2, this->buf, sizeof(uint32_t));
            memcpy(&id1, this->buf + sizeof(uint32_t), sizeof(uint64_t));
            TagID tagId = std::make_tuple(id1, id2);
            Serial.print(id1, HEX);
            Serial.println(id2, HEX);
            if (std::count(this->readTagIds.begin(), this->readTagIds.end(), tagId) == 0)
            {
                this->readTagIds.push_back(tagId);
            }
            this->bufSize = 0;
        }
        // USBSerial.print(">bufSize:");
        // USBSerial.println(this->bufSize);
        // USBSerial.print(">data:");
        // USBSerial.println(data, HEX);
    }
    if (!isEnd)
    {
        return;
    }

    this->tagIds.clear();
    for (auto tagId : this->readTagIds)
    {
        this->tagIds.push_back(tagId);
    }
    this->readTagIds.clear();
}

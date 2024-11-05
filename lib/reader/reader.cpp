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
    this->serial->write("start\n");
}

void Reader::stop()
{
    this->serial->write("stop\n");
}

std::vector<TagID> Reader::read()
{
    this->tagIds.clear();
    this->tagId = TagID();
    while (this->serial->available())
    {
        uint8_t receivedData[12];
        int index = 0;

        // 12バイトを受信するループ
        while (index < 12 && this->serial->available())
        {
            receivedData[index++] = this->serial->read();
        }

        // 改行文字が来るまで読み続ける
        if (this->serial->available() && this->serial->read() == '\n') {
            for(int i = 0; i < 12; i++) {
                USBSerial.print(receivedData[i], HEX);
                USBSerial.print(" ");
            }
            USBSerial.println();
            // 12バイトのデータをタプルに変換
            std::get<0>(this->tagId) = receivedData[0];
            std::get<1>(this->tagId) = receivedData[1];
            std::get<2>(this->tagId) = receivedData[2];
            std::get<3>(this->tagId) = receivedData[3];
            std::get<4>(this->tagId) = receivedData[4];
            std::get<5>(this->tagId) = receivedData[5];
            std::get<6>(this->tagId) = receivedData[6];
            std::get<7>(this->tagId) = receivedData[7];
            std::get<8>(this->tagId) = receivedData[8];
            std::get<9>(this->tagId) = receivedData[9];
            std::get<10>(this->tagId) = receivedData[10];
            std::get<11>(this->tagId) = receivedData[11];
            bool isDuplicate = false;
            for (auto tagid : this->tagIds)
            {
                if (tagid == this->tagId)
                {
                    isDuplicate = true;
                    break;
                }
            }

            if (!isDuplicate)
            {
                tagIds.push_back(tagId);
            }
        }
    }
    return tagIds;
}

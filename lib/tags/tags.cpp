#include "tags.hpp"

std::map<TagID, uint8_t> readTags(fs::FS &fs)
{
    auto temp = std::map<TagID, uint8_t>();
    USBSerial.println(fs.exists("/tags.bin") ? "File exists" : "File does not exist");
    if (!fs.exists("/tags.bin"))
    {
        return temp;
    }
    auto tags_file = fs.open("/tags.bin", FILE_READ);
    while (tags_file.available())
    {

        uint64_t tag_id_high;
        uint32_t tag_id_low;
        tags_file.readBytes((char *)&tag_id_high, sizeof(tag_id_high));
        tags_file.readBytes((char *)&tag_id_low, sizeof(tag_id_low));
        uint8_t value = tags_file.read();
    }
    tags_file.close();
    return temp;
}

void writeTags(fs::FS &fs, std::map<TagID, uint8_t> &tags)
{
    USBSerial.println(fs.exists(TAGS_FILE) ? "File exists" : "File does not exist");
    if (fs.exists(TAGS_FILE))
    {
        USBSerial.println("Removing existing tags file");
        fs.remove(TAGS_FILE); // 既存のファイルを削除
    }
    auto tags_file = fs.open(TAGS_FILE, FILE_WRITE, true);
    for (const auto &tag : tags)
    {
        uint64_t tag_id_high = std::get<0>(tag.first);
        uint32_t tag_id_low = std::get<1>(tag.first);
        uint8_t value = tag.second;
        tags_file.write((const uint8_t *)&tag_id_high, sizeof(tag_id_high));
        tags_file.write((const uint8_t *)&tag_id_low, sizeof(tag_id_low));
        tags_file.write(value);
    }
    tags_file.close();
}

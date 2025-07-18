#ifndef TAGS_HPP
#define TAGS_HPP
#include <map>
#include <SPIFFS.h>
#include <reader.h>

#define TAGS_FILE "/tags.bin"

std::map<TagID, uint8_t> readTags(fs::FS &fs);

void writeTags(fs::FS &fs, std::map<TagID, uint8_t> &tags);

#endif // TAGS_HPP

#include "draw.h"

Coordinate_t initCoordinate(int x, int y)
{
    return Coordinate_t{x, y};
}

inline bool betterDrawPngFile(M5GFX *display, fs::FS fs, const char *path, Coordinate_t coordinate, datum_t datum)
{
    return display->drawPngFile(fs, path, coordinate.x, coordinate.y, 0, 0, 0, 0, 1, 0, datum);
}

inline bool betterDrawPngFile(M5Canvas *canvas, fs::FS fs, const char *path, Coordinate_t coordinate, datum_t datum)
{
    return canvas->drawPngFile(fs, path, coordinate.x, coordinate.y, 0, 0, 0, 0, 1, 0, datum);
}

#ifndef __DRAW_H__
#define __DRAW_H__
#include <FS.h>
#include <M5GFX.h>

struct Coordinate_t
{
    int x;
    int y;
};

Coordinate_t initCoordinate(int x, int y);

inline bool betterDrawPngFile(M5GFX *display, fs::FS fs, const char *path, Coordinate_t coordinate, datum_t datum);
inline bool betterDrawPngFile(M5Canvas *canvas, fs::FS fs, const char *path, Coordinate_t coordinate, datum_t datum);

#endif

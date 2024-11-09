#ifndef __TIME__H__
#define __TIME__H__
#include "draw.h"
struct Time
{
    int hours;
    int minutes;
};

inline void timerset(M5Canvas &canvas, fs::FS &fs, int keta, Coordinate_t coordinate, datum_t datum)
{
    char path[32];
    sprintf(path, "/font/36p/%d.png", keta);
    
    betterDrawPngFile(&canvas, fs, path, coordinate, datum);
}

inline void timerchange(M5Canvas &canvas, fs::FS &fs, int keta, Coordinate_t coordinate, datum_t datum)
{
    char path[32];
    sprintf(path, "/font/32p/%d.png", keta);
    
    betterDrawPngFile(&canvas, fs, path, coordinate, datum);
}
#endif
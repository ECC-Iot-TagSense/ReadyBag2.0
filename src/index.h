#ifndef __index_h__
#define __index_h__

int updaterIndex(int currentIndex, int maxIndex, int direction)
{
    auto diff = 0;
    if (direction < 0)
    {
        diff = -1;
    }
    if (direction > 0)
    {
        diff = 1;
    }
    auto nextIndex = currentIndex + diff;

    if (nextIndex < 0)
    {
        nextIndex = maxIndex;
    }
    if (nextIndex > maxIndex)
    {
        nextIndex = 0;
    }
    return nextIndex;
}

#endif

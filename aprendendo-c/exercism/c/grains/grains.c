#include "grains.h"

uint64_t square(uint8_t index)
{
    if (index == 0)
    {
        return 0;
    }
    else if (index < 65)
    {
        return 1ULL << (index - 1);
    }
    else
    {
        return 0;
    }
}

uint64_t total(void)
{
    return ~0ULL;
}
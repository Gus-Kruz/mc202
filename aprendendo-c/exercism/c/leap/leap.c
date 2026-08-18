#include "leap.h"
#include <stdio.h>

bool leap_year(int year)
{
    if (year % 4 == 0)
    {
        if (year % 400 == 0)
        {
            return true;
        }

        else if (year % 100 == 0)
        {
            return false;
        }

        return true;
    }
    else
    {
        return false;
    }
}
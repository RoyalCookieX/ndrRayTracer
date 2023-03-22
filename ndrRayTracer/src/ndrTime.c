#include "ndrTime.h"
#include <time.h>
#include <stdio.h>

void ndrGetTime(ndrTime* result)
{
    *result = (ndrTime)time(NULL);
}

ndrTime ndrGetElapsedSeconds(ndrTime start, ndrTime end)
{
    if(end < start)
        return 0;

    return end - start;
}

void ndrPrintHHMMSS(ndrTime time)
{
    ndrTime hours = time / 3600;
    ndrTime minutes = time / 60;
    ndrTime seconds = time % 60;
    
    printf("%02llu:%02llu:%02llu Elapsed.\n", hours, minutes, seconds);
}
#pragma once
#include "defines.h"

// Gets the current time in seconds.
void ndrGetTime(ndrTime* result);
// Gets the elapsed time in seconds.
ndrTime ndrGetElapsedSeconds(ndrTime start, ndrTime end);
// Displays a duration of seconds into HH:MM:SS format.
void ndrPrintHHMMSS(ndrTime time); 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "energyAppFunctions.h"
/**
 * 
 * @brief Function to get the index for the print statement is the power green?
 * 
 * @param value The intensity struct as a pointer with the green value returen in the struct.
 * @return int Returns the 
 */

int GreenPower(DataStats *value)
{
    if (value->carbonIntensity <= 100)
    {
        return 0;
    }
    else if (value->carbonIntensity <= 200)
    {
        return 1;
    }
    else if (value->carbonIntensity <= 300)
    {
        return 2;
    }
    else
    {
        return 3;
    }
}



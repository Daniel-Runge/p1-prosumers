#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "energyAppFunctions.h"

#define SEC_PER_MIN 60
#define SEC_PER_HOUR (60 * 60)
#define SEC_PER_DAY (60 * 60 * 24)

/**
 * @brief The function converts UnixTime into a string
 * The function is taken from https://www.epochconverter.com/programming/c
 * @param unixNumber which needs to be of type time_t 
 */
void ConvertUnixDate(time_t unixNumber)
{
    struct tm ts;
    char prettyTime[50];
    char timeFormat[10] = "%c %Z";

    // Format time, "day yyyy-mm-dd hh:mm:ss tmz"
    ts = *localtime(&unixNumber);
    strftime(prettyTime, sizeof(prettyTime), timeFormat, &ts);
    printf("%s", prettyTime);
}

/**
 * @brief function which converts seconds into days, hours, minutes and seconds
 * 
 * @param sekunder calculated in TimeForWind
 * @param infoTime the struct that contains info calculated from the function  
 */

/*void SecondsConverter(long int seconds, TimeSplit *infoTime)
{
    int minutes, hours, days;
    days = (seconds / SEC_PER_DAY) % SEC_PER_MIN;
    hours = (seconds / SEC_PER_HOUR) % SEC_PER_MIN;
    minutes = (seconds / SEC_PER_MIN) % SEC_PER_MIN;
    seconds = seconds % SEC_PER_MIN;

    infoTime->sec = seconds;
    infoTime->min = minutes;
    infoTime->hour = hours;
    infoTime->day = days;
}*/

/**
 * @brief the function calculates the difference between the actual time and the prognosed time
 *       
 * @param windPower 48 hour forecast. We used this structure to find the best time where the wind blows the most
 * @param hoursAhead hours limit the amount of data that needs to be worked on
 */
void GetBestTimeForWind(WindData windPower[50], int hoursAhead, TimeSplit *infoTime, WindData sortedWinds[])
{
    int i;
    for (i = 0; i < hoursAhead; i++)
    {
        sortedWinds[i] = windPower[i];
    }
    
    

    qsort(sortedWinds, hoursAhead, sizeof(WindData), CompareWindSpeed);


    /*timeDifference = sortedWinds[0].unixTime - t;
    SecondsConverter(timeDifference, infoTime);*/
}

/**
 * @brief compares the element windSpeed from the structure WindData
 * @param a first element in the structure
 * @param b second element in the structure
 * @return positive int if the function is true
 */
int CompareWindSpeed(const void *a, const void *b)
{
    WindData *windDataA = (WindData *)a;

    WindData *windDataB = (WindData *)b;
    if (windDataA->windSpeed > windDataB->windSpeed)
        return -1;
    else 
        return 1;

    return 0;
}

/**
 * @brief Plots a graph of windspeed up to 48 hours in the future.
 * 
 * @param windPower is used to get windspeeds at each hour.
 * @param maxHours is used to change how far ahead into the future the graph should plot.
 */
void PlotForecast(WindData windPower[], int maxHours)
{
    int upperWS = 0, i, j;
    /* +0.5 is used to round up any numbers that need to be rounded up */
    for (i = 0; i < maxHours; i++)
    {
        if ((windPower[i].windSpeed + 0.5) > upperWS)
        {
            upperWS = (windPower[i].windSpeed + 0.5);
        }
    }
    /* Rounds up to the nearest 5 */
    if (upperWS >= 15)
    {
        upperWS = 20;
    }
    else if (upperWS >= 10)
    {
        upperWS = 15;
    }
    else if (upperWS >= 5)
    {
        upperWS = 10;
    }
    else if (upperWS >= 0)
    {
        upperWS = 5;
    }
    /* This for-loop starts at the top of the graph and goes down - Controls Y-axis */
    for (i = upperWS; i >= 0; i--)
    {
        if (i == 20 || i == 15 || i == 10 || i == 5 || i == 0)
        {
            printf("%2d m/s|", i);
        }
        else
        {
            printf("      |");
        }
        for (j = 0; j < maxHours; j++)
        {
            printf("  ");
            if ((windPower[j].windSpeed + 0.5) >= i - 1 && (windPower[j].windSpeed + 0.5) < i)
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("      ");
    for (i = 0; i <= maxHours * 3; i++)
    {
        printf("-");
    }
    printf("\n");
    printf("      ");
    for (i = 0; i < maxHours; i++)
    {
        if (i % 2 == 0)
        {
            printf("  %2d", i);
        }
        else
        {
            printf("  ");
        }
    }
    printf("\n");
    printf("      ");
    printf("%*s", (maxHours * 3 / 2) + 6, "Hours Ahead");
    printf("\n");
    printf("This graph shows the forecast windspeeds (measured in meters per second) \n"
    "at specific times (measured in hours) within the chosen forecast hours\n\n");
}
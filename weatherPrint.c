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
    char buf[80];

    // Format time, "day yyyy-mm-dd hh:mm:ss tmz"
    ts = *localtime(&unixNumber);
    strftime(buf, sizeof(buf), "%H", &ts);
    printf("%s", buf);
}

/**
 * @brief function which converts seconds into days, hours, minutes and seconds
 * 
 * @param sekunder calculated in TimeForWind
 * @param InfoTime the struct that contains info calculated from the function  
 */

void SecondsConverter(long int seconds, TimeSplit *InfoTime)
{
    long int minutes, hours, days;

    days = (seconds / SEC_PER_DAY) % SEC_PER_MIN;
    hours = (seconds / SEC_PER_HOUR) % SEC_PER_MIN;
    minutes = (seconds / SEC_PER_MIN) % SEC_PER_MIN;
    seconds = seconds % SEC_PER_MIN;

    InfoTime->sec = seconds;
    InfoTime->min = minutes;
    InfoTime->hour = hours;
    InfoTime->day = days;
}

/**
 * @brief the function calculates the difference between the actual time and the prognosed time
 *       
 * @param windPower 48 hour forecast. We used this structure to find the best time where the wind blows the most
 * @param hoursAhead hours limit the amount of data that needs to be worked on
 */
void TimeForWind(WindData windPower[50], int hoursAhead, TimeSplit *InfoTime)
{
    long int timeDifference;
    time_t t = time(NULL);

    qsort(windPower, hoursAhead, sizeof(WindData), ComparewindSpeed);

    timeDifference = windPower[0].unixTime - t;

    SecondsConverter(timeDifference, InfoTime);
}

/**
 * @brief compares the element windSpeed from the structure WindData
 * @param a first element in the structure
 * @param b second element in the structure
 * @return positive int if the function is true
 */
int ComparewindSpeed(const void *a, const void *b)
{
    WindData *windDataA = (WindData *)a;

    WindData *windDataB = (WindData *)b;

    return (windDataB->windSpeed - windDataA->windSpeed);
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
}
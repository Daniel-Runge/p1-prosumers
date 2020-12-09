#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#define SEC_PER_MIN 60
#define SEC_PER_HOUR (60 * 60)
#define SEC_PER_DAY (60 * 60 * 24)
typedef struct
{
    time_t UnixTime;
    double WindSpeed;
} WindData;

typedef struct
{
    long int sec;
    long int min;
    long int hour;
    long int day;
} TimeInfo;

void TimeForWind(WindData WindPower[50], int hoursAhead, TimeInfo *InfoTime);
void ConvertUnixDate(time_t unix_number);
void SecondsConverter(long int sekunder, TimeInfo *TimeInfo);
int CompareWindSpeed(const void *a, const void *b);

/**
 * @brief The function converts UnixTime into a string
 * The function is taken from https://www.epochconverter.com/programming/c
 * @param unix_number which needs to be of type time_t 
 */
void ConvertUnixDate(time_t unix_number)
{
    struct tm ts;
    char buf[80];

    // Format time, "ddd yyyy-mm-dd hh:mm:ss zzz"
    ts = *localtime(&unix_number);
    strftime(buf, sizeof(buf), "%H", &ts);
    printf("%s", buf);
}

/**
 * @brief the function converts the seconds 
 * 
 * @param sekunder calculated in TimeForWind
 * @param InfoTime the struct that contains info calculated from the function  
 */

void SecondsConverter(long int sekunder, TimeInfo *InfoTime)
{
    long int minutter, timer, dage;

    dage = (sekunder / SEC_PER_DAY) % SEC_PER_MIN;
    timer = (sekunder / SEC_PER_HOUR) % SEC_PER_MIN;
    minutter = (sekunder / SEC_PER_MIN) % SEC_PER_MIN;
    sekunder = sekunder % SEC_PER_MIN;

    InfoTime->sec = sekunder;
    InfoTime->min = minutter;
    InfoTime->hour = timer;
    InfoTime->day = dage;
}

/**
 * @brief the function calculates the difference between the actual time and the prognosed time
 *       
 * @param WindPower 48 hour forecast. We used this structure to find the best time where the wind blows the most
 * @param hoursAhead hours limit the amount of data that needs to be worked on
 */
void TimeForWind(WindData WindPower[50], int hoursAhead, TimeInfo *InfoTime)
{
    long int TimeDifference;
    time_t t = time(NULL);

    qsort(WindPower, hoursAhead, sizeof(WindData), CompareWindSpeed);

    TimeDifference = WindPower[0].UnixTime - t;

    SecondsConverter(TimeDifference, InfoTime);
}

/**
 * @brief compares the element WindSpeed from the structure WindData
 * @param a first element in the structure
 * @param b second element in the structure
 * @return positive int if the function is true
 */
int CompareWindSpeed(const void *a, const void *b)
{
    WindData *WindDataA = (WindData *)a;

    WindData *WindDataB = (WindData *)b;

    return (WindDataB->WindSpeed - WindDataA->WindSpeed);
}

/**
 * @brief Plots a graph of windspeed up to 48 hours in the future.
 * 
 * @param WindPower is used to get windspeeds at each hour.
 * @param MaxHours is used to change how far ahead into the future the graph should plot.
 */
void Plot(WindData WindPower[], int MaxHours)
{
    int UpperMS = 0, i, j;
    /* Finds the highest windspeed in the set we need to check */
    for (i = 0; i < MaxHours; i++)
    {
        if ((WindPower[i].WindSpeed + 0.5) > UpperMS)
        {
            UpperMS = (WindPower[i].WindSpeed + 0.5);
        }
    }
    /* Rounds up to the nearest 5 */
    if (UpperMS >= 15)
    {
        UpperMS = 20;
    }
    else if (UpperMS >= 10)
    {
        UpperMS = 15;
    }
    else if (UpperMS >= 5)
    {
        UpperMS = 10;
    }
    else if (UpperMS >= 0)
    {
        UpperMS = 5;
    }
    /* This for-loop starts at the top of the graph and goes down - Controls Y-axis */
    for (i = UpperMS; i >= 0; i--)
    {
        /* Draws the Y-axis and writes numbers periodically on the axis */
        if (i == 20 || i == 15 || i == 10 || i == 5 || i == 0)
        {
            printf("%2d m/s|", i);
        }
        else
        {
            printf("      |");
        }
        for (j = 0; j < MaxHours; j++)
        {
            printf("  ");
            if ((WindPower[j].WindSpeed + 0.5) >= i - 1 && (WindPower[j].WindSpeed + 0.5) < i)
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
    for (i = 0; i <= MaxHours * 3; i++)
    {
        printf("-");
    }
    printf("\n");
    printf("      ");
    for (i = 0; i < MaxHours; i++)
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
    printf("%*s", (MaxHours * 3 / 2) + 6, "Hours Ahead");
    printf("\n");
}
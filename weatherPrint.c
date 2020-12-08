#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#define SEC_PER_MIN 60
#define SEC_PER_HOUR (60 * 60)
#define SEC_PER_DAY (60 * 60 * 24)
#define SEC_PER_WEEK (60 * 60 * 24 * 7)

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
 * @brief the main function is filled with dummy data and it tests the functions
 * 
 * @return int 
 */
int main()
{
    int hoursAhead = 6;
    WindData WindPower[50];
    TimeInfo InfoTime;
    TimeForWind(WindPower, hoursAhead, &InfoTime);
    printf("%ld\n", InfoTime.day);
    printf("%ld\n", InfoTime.hour);
    printf("%ld\n", InfoTime.min);
    printf("%ld\n", InfoTime.sec);
    return 0;
}
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

    dage = (sekunder % SEC_PER_WEEK) / SEC_PER_DAY;
    timer = (sekunder % SEC_PER_DAY) / SEC_PER_HOUR;
    minutter = (sekunder % SEC_PER_HOUR) / SEC_PER_MIN;
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
    struct tm *local;
    time_t t = time(NULL);

    /* Get the localtime */
    local = localtime(&t);

    /*qsort sorts WindPower.WindSpeed in decreasing order*/
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
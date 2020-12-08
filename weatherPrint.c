#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
typedef struct
{
    time_t UnixTime;
    double WindSpeed;
} WindData;

int analyse_wind(WindData WindPower[50]);
void print_wind(WindData WindPower[50], int hoursAhead);
int CompareWindSpeed(const void *a, const void *b);
void ConvertUnixDate(time_t unix_number);

/**
 * @brief the main function is filled with dummy data and it tests the functions
 * 
 * @return int 
 */
int main()
{

    int hoursAhead = 6;
    WindData WindPower[50];
    int i;
    for (i = 0; i < 48; i++)
    {
        WindPower[i].WindSpeed = 4 + i;
        WindPower[i].UnixTime = i + 1607344339;
    }

    print_wind(WindPower, hoursAhead);

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
    strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S %Z", &ts);
    printf("%s", buf);
}

int analyse_wind(WindData WindPower[50])
{
    if (WindPower->WindSpeed <= 4)
    {
        return 0;
    }
    else if (WindPower->WindSpeed <= 6)
    {
        return 1;
    }
    else if (WindPower->WindSpeed <= 8)
    {
        return 2;
    }
    else if (WindPower->WindSpeed <= 10)
    {
        return 3;
    }
    else
    {
        return 4;
    }
}

/**
 * @brief this function prints the result from the function analyse_wind and tells whether it is a good time to consume the energy
 * 
 * 
 */
void print_wind(WindData WindPower[50], int hoursAhead)
{

    const char *about_wind[] = {
        "The energy is not comming from windmills right now, so know is not a good time\n",
        "Windmills are producing a small amount of energy right now, but not green\n",
        "The wind blows moderately, There could be a better time then now\n",
        "There is coming enough energy from windmills to call it green energy. Around this time would be a good time to use energy\n",
        "The wind is very high Around this time, so the windmills are producing a large amount of energy right now. Around this time it is the best time to consume energy\n"};
    printf("The wind speed will be shown as a scale from 0 to 4, where 4 shows that it is the best time to use energy\n");

    qsort(WindPower, hoursAhead, sizeof(WindData), CompareWindSpeed);
    int i;
    for (i = 0; i < hoursAhead; i++)
    {

        if (analyse_wind(&WindPower[i]) == 4)
        {
            ConvertUnixDate(WindPower[i].UnixTime);

            printf("The Time: %ld %s and %lf\n", WindPower[i].UnixTime, about_wind[4], WindPower[i].WindSpeed);
        }
        else if (analyse_wind(&WindPower[i]) == 3)
        {
            ConvertUnixDate(WindPower[i].UnixTime);

            printf("The Time: %ld %s and %lf\n", WindPower[i].UnixTime, about_wind[3], WindPower[i].WindSpeed);
        }
        else if (analyse_wind(&WindPower[i]) == 2)
        {
            ConvertUnixDate(WindPower[i].UnixTime);

            printf("The Time: %ld %s and %lf\n", WindPower[i].UnixTime, about_wind[2], WindPower[i].WindSpeed);
        }
        else if (analyse_wind(&WindPower[i]) == 1)
        {
            ConvertUnixDate(WindPower[i].UnixTime);

            printf("The Time: %ld %s and %lf\n", WindPower[i].UnixTime, about_wind[1], WindPower[i].WindSpeed);
        }
        else
        {
            ConvertUnixDate(WindPower[i].UnixTime);
            printf("The Time: %ld %s and %lf", WindPower[i].UnixTime, about_wind[0], WindPower[i].WindSpeed);
        }
    }
}

int CompareWindSpeed(const void *a, const void *b)
{

    WindData *WindDataA = (WindData *)a;

    WindData *WindDataB = (WindData *)b;

    return (WindDataB->WindSpeed - WindDataA->WindSpeed);
}
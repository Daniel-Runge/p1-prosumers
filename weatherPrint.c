#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
typedef struct
{
    int Time;
    double WindSpeed;
} Speed;

typedef struct
{
    int UnixTime;
    double WindSpeed;
} WindData;

int analyse_wind(WindData WindPower[50]);
void print_wind(Speed Speeds[50], WindData WindPower[50], int hours);
int compare(const void *a, const void *b);

/*int main()
{
    int hours = 3;
    Speed Speeds[50];
    WindData WindPower[50];
    WindPower[0].WindSpeed = 4.5;
    WindPower[1].WindSpeed = 5.5;
    WindPower[2].WindSpeed = 2.5;
    WindPower[0].UnixTime = 143289432;
    WindPower[1].UnixTime = 834270324;
    WindPower[2].UnixTime = 154328932;

    print_wind(Speeds, WindPower, hours);
    return 0;
}
*/
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
void print_wind(Speed Speeds[50], WindData WindPower[50], int hours)
{
    const char *about_wind[] = {
        "As the wind mills do not produce energy right now\n",
        "The wind mills produce small amounts of energy right now\n",
        "The wind blows moderately, which means it might be a good time to use energy\n",
        "The wind is blowing - you can consume energy\n",
        "Now there are big amounts of energy that are produced. Now it is the best time to consume energy\n"};

    int i;
    printf("The wind speed will be shown as a scale from 0 to 4, where 4 shows that it is the best time to use energy\n");

    qsort(WindPower, hours, sizeof(WindData), compare);

    /*perhaps for loop which prints for the next hours*/
    for (i = 0; i < hours; i++)
    {
        if (analyse_wind(&WindPower[i]) == 4)
        {
            printf("The Time: %d %s", WindPower->UnixTime, about_wind[4]);
        }
        else if (analyse_wind(&WindPower[i]) == 3)
        {
            printf("The Time: %d %s", WindPower->UnixTime, about_wind[3]);
        }
        else if (analyse_wind(&WindPower[i]) == 2)
        {
            printf("The Time: %d %s", WindPower->UnixTime, about_wind[2]);
        }
        else if (analyse_wind(&WindPower[i]) == 1)
        {
            printf("The Time: %d %s", WindPower->UnixTime, about_wind[1]);
        }
        else
        {
            printf("%s", about_wind[0]);
        }
    }
}

int compare(const void *a, const void *b)
{

    WindData *WindDataA = (WindData *)a;

    WindData *WindDataB = (WindData *)b;

    return (WindDataB->WindSpeed - WindDataA->WindSpeed);
}
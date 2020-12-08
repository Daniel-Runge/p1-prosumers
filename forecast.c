#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <json-c/json.h>
#include "energyAppFunctions.h"



/*
int main(void)
{
    get_api("w", "https://api.openweathermap.org/data/2.5/onecall?lat=56&lon=9.3&exclude=current,minutely,daily,alerts&appid=91f093992825e6f84a7a6f7033480686", "OpenWeatherMap.json", "91f093992825e6f84a7a6f7033480686");
    WeatherParser("OpenWeatherMap.json");
    Plot(WindPower, 25);
    return (0);
}
*/

/**
 * @brief Takes a json file and parses it for our wanted data(Time and windspeed). 
 * The data is then put into the WindPower struct.
 * 
 * @param Filename is the name of the file which we need to open and parse.
 */
void WeatherParser(char *Filename, WindData WindPower[])
{
    FILE *fp;
    char FileBuffer[15000];
    int i, NumOfHours;
    struct json_object *Full_json;
    struct json_object *AllHours;
    struct json_object *SingleHour;
    struct json_object *Time;
    struct json_object *Wind;
    /*Opens file, reads data and puts data in 'FileBuffer'*/
    fp = fopen(Filename, "r");
    if (fp == NULL)
    {
        printf("Could not read JSON file\n");
    }
    fread(FileBuffer, 15000, 1, fp);
    fclose(fp);

    /*Takes FileBuffer and puts it in Full_json struct, so it now is a json_object*/
    Full_json = json_tokener_parse(FileBuffer);
    /*Looks for 'hourly' from json file and puts 'hourly' array into the 'AllHours' json_object*/
    json_object_object_get_ex(Full_json, "hourly", &AllHours);
    /*Gives us the amount of hours we have forecasts for*/
    NumOfHours = json_object_array_length(AllHours);
    printf("%d\n", NumOfHours);
    /*for-loop puts data from every hour in correct place in the WindPower struct
    unixTime = Time
    WindSpeed = Wind*/
    for (i = 0; i < NumOfHours; i++)
    {
        SingleHour = json_object_array_get_idx(AllHours, i);
        json_object_object_get_ex(SingleHour, "dt", &Time);
        json_object_object_get_ex(SingleHour, "wind_speed", &Wind);
        WindPower[i].UnixTime = json_object_get_int(Time);
        WindPower[i].WindSpeed = json_object_get_double(Wind);
    }
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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <json-c/json.h>

/* Struct for our found data */
struct WindData
{
    int UnixTime;
    double WindSpeed;
};
/* We get an array of size 48 from the API, this is size 50 for safety's sake */
typedef struct WindData WindData;
WindData WindPower[50];

    /*get_api("w", "https://api.openweathermap.org/data/2.5/onecall?lat=56&lon=9.3&exclude=current,minutely,daily,alerts&appid=91f093992825e6f84a7a6f7033480686", "OpenWeatherMap.json", "91f093992825e6f84a7a6f7033480686");
    WeatherParser("OpenWeatherMap.json");*/


/**
 * @brief Takes a json file and parses it for our wanted data(Time and windspeed). 
 * The data is then put into the WindPower struct.
 * 
 * @param Filename is the name of the file which we need to open and parse.
 */
void WeatherParser(char *Filename)
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
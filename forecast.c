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
struct WindData WindPower[50];
typedef struct WindData WindData;
/* Prototypes */
void get_api(char *filemode, char *url, char *filename, char *auth);
void WeatherParser(char *Filename);

/* Delete when file is complete */
int main(void)
{
    get_api("w", "https://api.openweathermap.org/data/2.5/onecall?lat=56&lon=9.3&exclude=current,minutely,daily,alerts&appid=91f093992825e6f84a7a6f7033480686", "OpenWeatherMap.json", "91f093992825e6f84a7a6f7033480686");
    WeatherParser("OpenWeatherMap.json");
    return (0);
}

/* Delete when file is complete */
void get_api(char *filemode, char *url, char *filename, char *auth)
{

    CURL *curl;
    FILE *fp;
    struct curl_slist *headers = NULL;
    CURLcode result;

    /* creates a file and a pointer to that file  */
    fp = fopen(filename, filemode);

    /* this is setting up the request type "GET" and the adress curl should access  */
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(curl, CURLOPT_URL, url);

    /* creates a header file and puts the authentification token into it for the curl request  */
    headers = curl_slist_append(headers, auth);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    /*  tells curl that you want to write the data you get into your file */
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    /* curl_easy_perform runs the curl that you set using easy_setopt */
    result = curl_easy_perform(curl);

    /* closes everything and cleans up */
    fclose(fp);
    curl_easy_cleanup(curl);
}

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
    struct json_object *Hourly;
    struct json_object *EveryHour;
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
    /*Looks for 'hourly' from json file and puts 'hourly' array into the 'Hourly' json_object*/
    json_object_object_get_ex(Full_json, "hourly", &Hourly);
    /*Gives us the amount of hours we have forecasts for*/
    NumOfHours = json_object_array_length(Hourly);
    printf("%d\n", NumOfHours);
    /*for-loop puts data from every hour in correct place in the WindPower struct
    unixTime = Time
    WindSpeed = Wind*/
    for (i = 0; i < NumOfHours; i++)
    {
        EveryHour = json_object_array_get_idx(Hourly, i);
        json_object_object_get_ex(EveryHour, "dt", &Time);
        json_object_object_get_ex(EveryHour, "wind_speed", &Wind);
        WindPower[i].UnixTime = json_object_get_int(Time);
        WindPower[i].WindSpeed = json_object_get_double(Wind);
        printf("%d - %lf\n", WindPower[i].UnixTime, WindPower[i].WindSpeed);
    }
}
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

void Plot(WindData WindPower[]);
void WeatherParser(char *Filename);
void get_api(char *filemode, char *url, char *filename, char *auth);

int main(void)
{
    get_api("w", "https://api.openweathermap.org/data/2.5/onecall?lat=56&lon=9.3&exclude=current,minutely,daily,alerts&appid=91f093992825e6f84a7a6f7033480686", "OpenWeatherMap.json", "91f093992825e6f84a7a6f7033480686");
    WeatherParser("OpenWeatherMap.json");
    Plot(WindPower);
    return (0);
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

void Plot(WindData WindPower[])
{
    int Big = 0, i, j, MaxHours = 25;
    for (i = 0; i < MaxHours; i++)
    {
        if ((WindPower[i].WindSpeed + 0.5) > Big)
        {
            Big = (WindPower[i].WindSpeed + 0.5);
        }
    }
    if (Big >= 15)
    {
        Big = 20;
    }
    else if (Big >= 10)
    {
        Big = 15;
    }
    else if (Big >= 5)
    {
        Big = 10;
    }
    else if (Big >= 0)
    {
        Big = 5;
    }
    for (i = Big; i >= 0; i--)
    {
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
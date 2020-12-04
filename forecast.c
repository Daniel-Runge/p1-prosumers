#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

struct WindData
{
    int UnixTime;
    int WindSpeed;
};


void get_api (char* filemode, char* url, char* filename, char* auth);


/**
 * @brief Get the file from a url  to the electricity map api
 * 
 */
int main(void)
{
    get_api("w", "https://api.openweathermap.org/data/2.5/onecall?lat=56&lon=9.3&exclude=current,minutely,daily,alerts&appid=91f093992825e6f84a7a6f7033480686", "OpenWeatherMap.json", "91f093992825e6f84a7a6f7033480686");
    return(0);
}


void get_api (char* filemode, char* url, char* filename, char* auth)
{

    CURL *curl;
    FILE *fp;
    struct curl_slist *headers = NULL;
    CURLcode result;
    
    /* creates a file and a pointer to that file  */
    fp=fopen(filename, filemode);

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

int analyse(struct WindData *number)
{

    if (number->WindSpeed <= 2)
    {
        return 0;
    }
    else if (number->WindSpeed <= 3)
    {
        return 1;
    }
    else if (number->WindSpeed <= 4)
    {
        return 2;
    }
    else if (number->WindSpeed <= 5)
    {
        return 3;
    }
    else
    {
        return 4;
    }
}



double EnergyParser(char *Filename, char *KeyWord)
{
    FILE *fp;
    char FileBuffer[1800];
    struct json_object *Full_json;
    struct json_object *Consumption;
    struct json_object *FoundNumber;
    fp = fopen(Filename, "r");
    if (fp == NULL)
    {
        printf("Could not read JSON file\n");
    }
    fread(FileBuffer, 1800, 1, fp);
    fclose(fp);

    Full_json = json_tokener_parse(FileBuffer);
    json_object_object_get_ex(Full_json, KeyWord, &FoundNumber);
    if (json_object_get_int(FoundNumber) == 0)
    {
        json_object_object_get_ex(Full_json, "powerConsumptionBreakdown", &Consumption);
        json_object_object_get_ex(Consumption, KeyWord, &FoundNumber);
    }
    return (json_object_get_int(FoundNumber));
}
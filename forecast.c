#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

void weathermap_api();



/**
 * @brief Get the file from a url  to the electricity map api
 * 
 */
void weathermap_api(char *filemode, char *url, char *filename)
{

    CURL *curl;
    FILE *fp;
    struct curl_slist *headers = NULL;
    CURLcode result;

    /* creates a file and a pointer to that file  */
    fp = fopen("OpenWeatherMap.json", "w");

    /* this is setting up the request type "GET" and the adress curl should access  */
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(curl, CURLOPT_URL, "https://api.openweathermap.org/data/2.5/onecall?lat=56&lon=9.3&exclude=minutely,daily,alerts&appid=91f093992825e6f84a7a6f7033480686");

    /* creates a header file and puts the authentification token into it for the curl request  */
    headers = curl_slist_append(headers, "auth-token: 91f093992825e6f84a7a6f7033480686");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    /*  tells curl that you want to write the data you get into your file */
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    /* curl_easy_perform runs the curl that you set using easy_setopt */
    result = curl_easy_perform(curl);

    /* closes everything and cleans up */
    fclose(fp);
    curl_easy_cleanup(curl);
}
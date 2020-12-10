#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>


void ContactApi (char* filemode, char* url, char* filename, char* auth);
void GetApiFiles(char location);

/**
 * @brief the program accesses the electricity map api and downloads data from dk and inputs it into a file
 * 
 */

void GetApiFiles(char location)
{
    char* url[] = { "https://api.electricitymap.org/v3/power-breakdown/latest?zone=DK-DK1",
     "https://api.electricitymap.org/v3/power-breakdown/latest?zone=DK-DK2", 
     "https://api.electricitymap.org/v3/carbon-intensity/latest?zone=DK-DK1", 
     "https://api.electricitymap.org/v3/carbon-intensity/latest?zone=DK-DK2", 
     "https://api.openweathermap.org/data/2.5/onecall?lat=56&lon=9.3&exclude=current,minutely,daily,alerts&appid=91f093992825e6f84a7a6f7033480686"};
    
    char* filemode[] ={"w","a"};
    
    char* filename[] = {"renewable.json", "carbonIntensity.json", "OpenWeatherMap.json"};

    printf("\n%c\n",location);
    if(location == 'e'){
        ContactApi(filemode[0],url[1],filename[0], "auth-token: aRcMAViDADF2TuzMvUp3xFg6");
        ContactApi(filemode[0],url[3],filename[1], "auth-token: aRcMAViDADF2TuzMvUp3xFg6");
    }
    if(location == 'w'){
        ContactApi(filemode[0],url[0],filename[0], "auth-token: aRcMAViDADF2TuzMvUp3xFg6");
        ContactApi(filemode[0],url[2],filename[1], "auth-token: aRcMAViDADF2TuzMvUp3xFg6");
    }

    ContactApi(filemode[0], url[4], filename[2], "91f093992825e6f84a7a6f7033480686");
}

/**
 * @brief Get the file from a url to the electricity map api
 * 
 */
void ContactApi(char* filemode, char* url, char* filename, char* auth)
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
    printf("API contact done\n");
}


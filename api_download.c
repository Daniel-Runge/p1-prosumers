#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>


void get_co2 (void);
void get_api (char filemode, char* url);

/**
 * @brief the program accesses the electricity map api and downloads data from dk and inputs it into a file
 * 
 */


int main (void)
{
    /*runs two functions that together download data from electricity map */

    char* url = "https://api.electricitymap.org/v3/power-breakdown/latest?zone=DK-DK1";
    
    get_api('w',url);
    get_co2();


}

/**
 * @brief Get the renevables file from api
 * 
 */
void get_api (char filemode, char* url)
{

    CURL *curl;
    FILE *fp;
    int result;
    
    /* creates a file and a pointer to that file  */
    fp=fopen("testing.json", filemode);

    /* this is setting up the request type "GET" and the adress curl should access  */
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(curl, CURLOPT_URL, url);

    /* creates a header file and puts the authentification token into it for the curl request  */
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "auth-token: aRcMAViDADF2TuzMvUp3xFg6");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    /*  tells curl that you want to write the data you get into your file */
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    result = curl_easy_perform(curl);

    /* closes everything and cleans up */
    fclose(fp);
    curl_easy_cleanup(curl);

}

/**
 * @brief Get the co2 intensity file from api
 * 
 */
void get_co2 (void)
{
    
    CURL *curl;
    FILE *fp;
    int result;
    
    /* opens a file and adds to the end and and creates a pointer to that file  */
    fp=fopen("testing.json", "a");

    /* this is setting up the request type "GET" and the adress curl should access  */
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(curl, CURLOPT_URL, "https://api.electricitymap.org/v3/carbon-intensity/latest?zone=DK-DK1");

    /* creates a header file and puts the authentification token into it for the curl request  */
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "auth-token: aRcMAViDADF2TuzMvUp3xFg6");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    /*  tells curl that you want to write the data you get into your file */
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    result = curl_easy_perform(curl);

    /* closes everything and cleans up */
    fclose(fp);
    curl_easy_cleanup(curl);



}
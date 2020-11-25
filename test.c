#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>


void get_co2 (void);
void get_renevable (void);
/* the program accesses the electricity map api and downloads data from dk and inputs it into a file*/

int main (void)
{
    /*runs two functions that together download data from electricity map */

    get_renevable();
    get_co2();


}


void get_renevable (void)
{

    CURL *curl;
    FILE *fp;
    int result;
    
    /* creates a file and a pointer to that file  */
    fp=fopen("testing.json", "w");

    /* this is setting up the request type "GET" and the adress curl should access  */
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(curl, CURLOPT_URL, "https://api.electricitymap.org/v3/power-breakdown/latest?zone=DK-DK1");

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

    get_co2();
    /*get co2 density*/

}


void get_co2 (void)
{
    /*get co2 density*/
    
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
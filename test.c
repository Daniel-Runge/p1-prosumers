#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

int main (void)
{
    
    printf("hello");
    CURL *curl;
    FILE *fp;
    int result;
    

    fp=fopen("testing.json", "wb");

    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(curl, CURLOPT_URL, "https://api.electricitymap.org/v3/power-breakdown/latest?zone=DK-DK1");


    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "auth-token: aRcMAViDADF2TuzMvUp3xFg6");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    result = curl_easy_perform(curl);


    fclose(fp);
    curl_easy_cleanup(curl);

}
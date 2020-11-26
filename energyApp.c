#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "energyAppFunctions.h"



int main(void)
{
    CURL *curl;
    CURLcode res;
    FILE *fp;

    /* curl_global_init(CURL_GLOBAL_ALL); */
    get_co2();
    get_renevable();

    /*curl_global_cleanup();*/
}
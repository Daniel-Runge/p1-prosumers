#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "energyAppFunctions.h"



int main(void)
{
    data_total total;
    /* curl_global_init(CURL_GLOBAL_ALL); */

    filemaker();
    readFile(total);
    /*curl_global_cleanup();*/
    return 0;
}

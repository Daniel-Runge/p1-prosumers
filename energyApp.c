#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "energyAppFunctions.h"



int main(void)
{
    data_total total;
    data_consumtion consum;
    /* curl_global_init(CURL_GLOBAL_ALL); */

    fileMaker();
    readFile(&total);
    green_power(&total);
    welcomeprint();
    printdata(total, consum, green_power(&total));
    /*curl_global_cleanup();*/
    return 0;
}

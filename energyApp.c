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
    printf("1. %lf\n", total.renewable);
    readFile(&total);
    printf("2. %lf\n", total.renewable);
    green_power(&total);
    printf("3. %lf\n", total.renewable);
    welcomeprint();
    printdata(total, consum, green_power(&total));
    /*curl_global_cleanup();*/
    return 0;
}

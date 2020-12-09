#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "energyAppFunctions.h"

/**
 * @brief WRITE THIS MAIN FUNCTION PROPERLY! 
 */
int main(void)
{
    WindData windData[50];
    int hours = 6;
    TimeInfo timeInfo;
    int i;
    int j = 1;

    for(i = 0; i < 50; i++){
        windData[i].UnixTime = 1607441791 + i * 3671;
        windData[i].WindSpeed = 11 * i * j;
        j = j*-1;
    }

    TimeForWind(windData, hours, &timeInfo);
    printf("%ld\n", timeInfo.day);
    printf("%ld\n", timeInfo.hour);
    printf("%ld\n", timeInfo.min);
    printf("%ld\n", timeInfo.sec);


    return 0;
}

/**
 * @brief THIS FUNCTION HAS TO BE MOVED TO A DIFFERENT FILE.
 * 
 * @param settings 
 * @return char 
 */
char Command(settings settings)
{
    printf("chose a command, write '-h' for help\n");
    char choice;
    choice = CharInput();

    switch (choice)
    {
    case 'h':
        printf("-h to open help \n-s to change settings \n -g to do graphs\n -r to run the \b -e to exit the program\n");
        return 'h';
        break;
    case 's':
        printf("lets open settings then\n");
        UpdateSettingsMenu(settings);
        return 's';
        break;
    case 'g':
        printf("not yet implemented");
        return 'g';
        break;
    case 'r':
        printf("here we go again\n");
        return 'r';
        break;
    case 'e':
        printf("thanks for using\n");
        return 'e';
        break;
    default:
        printf("not a valid input\n");
        return 'z';
        break;
    }
}
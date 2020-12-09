#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "energyAppFunctions.h"

void runprogram(settings settings);

/**
 * @brief WRITE THIS MAIN FUNCTION PROPERLY! 
 */
int main(void)
{
    EnergiApp();
    return 0;
}
void EnergiApp(void)
{
    data_consumption consumtion;

    data_total total;

    settings settings;

    WindData Windpower[50];

    TimeInfo InfoTime;
    welcomeprint();
    do
    {
        if (CheckSettings())
        {
            runprogram(settings);
        }
        else
        {
            CreateSettings(settings);
            runprogram(settings);
        }
    }
    while (Command(settings)!='e');  
}

void runprogram(settings settings)
{
    data_consumption consumtion;
    data_total total;
    readFile(&total);
    printdata(total, consumtion, settings);

    
    




    






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
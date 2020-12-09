#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "energyAppFunctions.h"

void RunProgram(Settings settings);

/**
 * @brief WRITE THIS MAIN FUNCTION PROPERLY! 
 */
int main(void)
{
    EnergyApp();
    return 0;
}
void EnergyApp(void)
{
    settings settings;
    settings.forecast=1;
    settings.location='w';
    settings.numberOfHours=8;

    welcomeprint();
    if (!CheckSettings())
    {
        CreateSettings(settings);
    }
    runprogram(settings);
    while (Command(settings) != 'e')
    {
    }
main
}

void runprogram(Settings settings)
{
    DataConsumption consumtion;
    DataStats total;
    WindData windpower[50];
    TimeSplit InfoTime;
    readFile(&total);
    PrintData(total, consumtion, settings);

    if (settings.forecast)
    {
        printf("hello\n");
        WeatherParser("OpenWeatherMap.json", windpower);
        GetBestTimeForWind(windpower, settings.numberOfHours, &InfoTime);
    }
}

/**
 * @brief THIS FUNCTION HAS TO BE MOVED TO A DIFFERENT FILE.
 * 
 * @param settings 
 * @return char 
 */
char Command(Settings settings)
{
    printf("chose a command, write '-h' for help\n");
    char choice;
    choice = GetUserCharInput();

    switch (choice)
    {
    case 'h':
        printf("-h to open help\n -s to change settings\n -g to do graphs\n -r to run the\b -e to exit the program\n");
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
        RunProgram(settings);
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
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
    Settings settings;

    WelcomePrint();
    if (!CheckSettings())
    {

        settings = CreateSettings();
    }
    CreateSettingsStruct(&settings);
    RunProgram(settings);
    while (Command(&settings) != 'e')
    {
    }
}

void RunProgram(Settings settings)
{
    DataStats total;
    WindData windpower[50];
    TimeSplit InfoTime;
    GetApiFiles(settings.location);
    PrepareParsing(&total);

    if (settings.forecast)
    {
        WeatherParser("OpenWeatherMap.json", windpower);
        GetBestTimeForWind(windpower, settings.numberOfHours, &InfoTime);
    }
    PrintData(total, settings, InfoTime, windpower);
}

/**
 * @brief What does Command do?
 * 
 * @param settings 
 * @return char 
 */
char Command(Settings *settings)
{
    printf("Choose a command, write '-h' for help\n");
    char choice;
    choice = GetUserCharInput();

    switch (choice)
    {
    case 'h':
        printf("-h to open help\n -s to change settings\n -g to do graphs\n -r to run the\b -e to exit the program\n");
        return 'h';
        break;
    case 's':
        printf("Lets open settings then\n");
        UpdateSettingsMenu(settings);
        printf("Loc: %c Hours: %d FC: %d Carbon: %d Plot: %d", settings->location, settings->numberOfHours, settings->forecast, settings->CO2Intensity, settings->plot);
        return 's';
        break;
    case 'g':
        printf("Not yet implemented\n");
        return 'g';
        break;
    case 'r':
        printf("Here we go again\n");
        RunProgram(*settings);
        return 'r';
        break;
    case 'e':
        printf("Thanks for using\n");
        return 'e';
        break;
    default:
        printf("Not a valid input\n");
        return 'z';
        break;
    }
}
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
    while (Command(&settings) != 'q')
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
        printf("-h to open the help menu\n-s to change program settings\n-r to run the program again\n-q to quit the program\n");
        return 'h';
        break;
    case 's':
        printf("Opening settings\n");
        UpdateSettingsMenu(settings);
        return 's';
        break;
    case 'r':
        printf("Running the program again\n");
        RunProgram(*settings);
        return 'r';
        break;
    case 'q':
        printf("Thanks for using\n");
        return 'q';
        break;
    default:
        printf("Not a valid input, please try again\n");
        return 'z';
        break;
    }
}
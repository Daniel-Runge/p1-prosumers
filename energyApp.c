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
    settings.forecast = 1;
    settings.location = 'w';
    settings.numberOfHours = 8;


    WelcomePrint();
    if (!CheckSettings())
    {
        CreateSettings(settings);
    }
    RunProgram(settings);
    while (Command(settings) != 'e')
    {
    }
}

void RunProgram(Settings settings)
{
    DataStats total;
    WindData windpower[50];
    TimeSplit InfoTime;
    PrepareParsing(&total);
    PrintData(total, settings);

    if (settings.forecast)
    {
        printf("hello\n");
        WeatherParser("OpenWeatherMap.json", windpower);
        GetBestTimeForWind(windpower, settings.numberOfHours, &InfoTime);
    }
}
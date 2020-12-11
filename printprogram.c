#include <stdio.h>
#include "energyAppFunctions.h"

void WelcomePrint();

const char *carbonReponse[] = {
    /*this needs to change*/
    "very green.\n",
    "sonewhat green.\n",
    "a little bit green.\n",
    "not green at all.\n"};
const char *windResponse[] = {
    /*this needs to change and also what do we use it for*/
    "There is medicore wind in Denmark right now",
    "There is not much energy coming from the wind right now",
    "it blows a half pelican"};
/*int main()
{
    welcomeprint();
    printdata();
    return 0;
}*/
/**
 * @brief It is not finished
 * 
 */
void WelcomePrint()
{
    printf("           ____        ____  ______    __        _____     _____      ___  ___      ______  \n");
    printf("           \\   \\  __  /   / |   ___|  |  |      /  ___|   /     \\    /   \\/   \\    |   ___| \n");
    printf("            \\   \\/  \\/   /  |  |__    |  |     |  /      |  / \\  |  /          \\   |  |__ \n");
    printf("             \\          /   |  |___   |  |___  |  \\___   |  \\ /  | /   /\\__/\\   \\  |  |___ \n");
    printf("              \\___/\\___/    |______|  |______|  \\_____|   \\_____/ /___/      \\___\\ |______| \n");

    /*this needs to change*/
    printf("               Hello and welcome to energy data program. This program is able show you\n"
           "               if the electricity consumed in denmark is green or not. It can also show when\n"
           "               it will probably be green in the next 48 hours based on wind preditions.\n\n"
           "               There can be made changes on what you want to see in the program.\n"
           "               This can be done with the settings.\n"
           "               To use any commands always use '-' before any input.\n"
           "               If you need help simply press '-h' to go to the help menu.\n\n\n");
}
/**
 * @brief this is where the data will be printed, based on settings
 * 
 * DataStats total, int parameter, int wind
 * 
 *
 */
void PrintData(DataStats total, Settings settings, TimeSplit InfoTime, WindData windpower[])
{
    char *formatLine[] = {"|"};
    /*these strings maybe needs to change*/

    printf("\n\n\n Renewable energy (%%) |");
    if (settings.CO2Intensity)
    {
        printf(" Carbon intensity (g CO2/kWh) |");
    }
    printf("\n");
    /*printf(" The conclusion\n");*/
    printf(" %10.0f%12s", total.renewable, formatLine[0]);
    if (settings.CO2Intensity)
    {
        printf(" %15.0f%15.2s", total.carbonIntensity, formatLine[0]);
    }
    /*printf(" %10s \n", carbonReponse[GreenPower(&total)]);*/

    printf("\n\nThe energy is %s\n", carbonReponse[GreenPower(&total)]);

    if (settings.forecast)
    {
        printf("The best time is %d day %d hours %d mins %d secs from now\n", InfoTime.day, InfoTime.hour, InfoTime.min, InfoTime.sec);
        if (settings.plot)
        {
            PlotForecast(windpower, settings.numberOfHours);
        }
    }
}

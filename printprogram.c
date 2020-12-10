#include <stdio.h>
#include "energyAppFunctions.h"

void WelcomePrint();

const char *carbonReponse[] = {
    /*this needs to change*/
    "Green.\n",
    "Partialy green.\n",
    "Not green.\n",
    "very not green.\n"};
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
           "               This can be done with the settings. To use the settings always use '-'\n"
           "               before a setting is changed.\n"
           "               If you need help simply press '-h' to go to the help menu.\n\n\n");
}
/**
 * @brief this is where the data will be printed, based on settings
 * 
 * DataStats total, int parameter, int wind
 * 
 *
 */
void PrintData(DataStats total, Settings settings, TimeSplit InfoTime)
{
    char *formatLine[] = {"|"};
    /*these strings maybe needs to change*/
    
    printf(" Renewabele energy (%%) |");
    if (settings.CO2Intensity)
        printf(" Carbon intensity (CO2/kWh) |");

    printf(" The conclusion\n");
    printf(" %11.0f%12s", total.renewable, formatLine[0]);
    if (settings.CO2Intensity)
        printf(" %14.0f%14.2s", total.carbonIntensity, formatLine[0]);
    printf(" %10s \n", carbonReponse[GreenPower(&total)]);

    if (1)
    {
        printf("\nThe energy is %s\n", carbonReponse[GreenPower(&total)]);
    }

    if (settings.forecast)
    {
        printf("the best time is %d day %d hours %d mins %d secs.\n", InfoTime.day, InfoTime.hour, InfoTime.min, InfoTime.sec);
    }
}

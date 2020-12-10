#include <stdio.h>
#include "energyAppFunctions.h"

void WelcomePrint();
void PrintData(DataStats total, Settings settings);

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
    printf("              Hello and welcome to energy data program. This program is able show you\n"
           "           if the electricity consumed in denmark is green or not. It can also show when\n"
           "              it will probably be green in the next 48 hours based on wind preditions.\n\n");
}
/**
 * @brief this is where the data will be printed, based on settings
 * 
 * DataStats total, int parameter, int wind
 * 
 *
 */
void PrintData(DataStats total, Settings settings)
{
    char *formatLine[] = {"|"};
    /*these strings maybe needs to change*/
    printf("%% renewable energy | Carbon intensity (g/kWh) | Conclusion\n");

    printf("%11.2f%9s %14.2f%12s %10s \n", total.renewable, formatLine[0], total.carbonIntensity, formatLine[0], carbonReponse[GreenPower(&total)]);

    if (1)
    {
        printf("\nThe energy is %s\n", carbonReponse[GreenPower(&total)]);
    }

    /*printf("The total amount of energy in Denmark is produced by\n");
    printf("|Wind     Hydro     Biomass|\n");
    printf("|%4f   %4f   %7f|\n", consumtion.wind, consumtion.hydro, consumtion.biomass);*/
}
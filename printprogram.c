#include <stdio.h>
#include "energyAppFunctions.h"

void welcomeprint();
void printdata(data_total total, data_consumption consumtion, settings settings);

const char *co2[] = {
    /*this needs to change*/
    "Green.\n",
    "Partialy green.\n",
    "Not green.\n",
    "very not green.\n"};
const char *windy[] = {
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
void welcomeprint()
{
    /*this needs to change*/
    printf("Hello and welcome to energy data program. This program is able show you "
    "if the electricity consumed in denmark is green or not. It can also show when"
    " it will probably be green in the next 48 hours based on wind preditions.\n\n");
}
/**
 * @brief this is where the data will be printed, based on settings
 * 
 * data_total total, int parameter, int wind
 * 
 *
 */
void printdata(data_total total, data_consumption consumtion,/*here we need to change the prototype in the header file to match*/
 settings settings)
{
    char *empty[] = {"|"};
    /*these strings maybe needs to change*/
    printf("%% renewable energy | Carbon intensity (g/kWh) | Conclusion\n");

    printf("%11.2f%9s %14.2f%12s %10s \n", total.renewable,empty[0], total.carbon_intensity, empty[0], co2[green_power(&total)]);

    if (settings.green){
        print("\nThe energy is %s\n",co2[green_power(&total)])
    }

    if (settings.forecast){
        RunForecast();
    }

    if(/*need new setting for plot*/settings.forecats){
        plot(windpower[])
    }


    /*printf("The total amount of energy in Denmark is produced by\n");
    printf("|Wind     Hydro     Biomass|\n");
    printf("|%4f   %4f   %7f|\n", consumtion.wind, consumtion.hydro, consumtion.biomass);*/
}
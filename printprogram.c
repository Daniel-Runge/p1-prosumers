#include <stdio.h>
#include "energyAppFunctions.h"
/**
     * @brief a welcome message in the making, this is just an outcast
     * 
     * , int wind
     */
void welcomeprint();
void printdata(data_total total, data_consumption consumtion, int parameter);

const char *co2[] = {
    "Green!!\n",
    "The energy in Denmark is partialy green right now\n",
    "There are owls in the swamp\n",
    "The ice is smelting at the pøules\n"};
const char *windy[] = {
    "There is medicore wind in Denmark right now",
    "There is not much energy coming from the wind right now",
    "it blows a half pelican"};
/**
 * @brief It is not finished
 * 
 */
void welcomeprint()
{
    printf("Hello and welcome to our energy data program. This program can show you how Denmark "
           "produce their electrical energy right now. In Denmark we mainly use windpower to produce "
           "electricity, as windpower is not 100 procent consistent, the electrical power grid in Denmark "
           "sometimes has surplus of energy, this means that Denmark sells its electricity to other countries, "
           "and when the energy production is low, Denmark buys energy. This is all being displaced in this "
           "program.\n\n");
}
/**
 * @brief this is where the dat will be printed
 * 
 * data_total total, int parameter, int wind
 * 
 */
void printdata(data_total total, data_consumption consumtion, int parameter)
{
    char *empty[] = {"|"};
    printf("%% renewable energy | Carbon intensity (g/kWh) | Conclusion |\n");

    printf("%11.2f%9s %14.2f%12s %10s \n", total.renewable,empty[0], total.carbon_intensity, empty[0], co2[parameter]);


    /*printf("The total amount of energy in Denmark is produced by\n");
    printf("|Wind     Hydro     Biomass|\n");
    printf("|%4f   %4f   %7f|\n", consumtion.wind, consumtion.hydro, consumtion.biomass);*/
}
#include <stdio.h>
#include "energyAppFunctions.h"
/**
     * @brief a welcome message in the making, this is just an outcast
     * 
     */
void welcomeprint();
void printdata(data_total total, /*data_consumption consumtion*/, int parameter, int wind);

const char *co2[] = {
    "Right now the energy in denmark is green\n",
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
 */
void printdata(data_total total, /* data_consumption consumtion*/, int parameter, int wind)
{

    printf("Right now the procent of renewable energy in Denmark is %f\n", total.renewable);
    printf("The carbon intensity in Denmark is %f g/kWh\n", total.carbon_intensity);

    printf("So the conclusion must be \n%s\n", co2[parameter]);
    printf("%s\n", windy[wind]);
    /*printf("The total amount of energy in Denmark is produced by\n");
    printf("|Wind     Hydro     Biomass|\n");
    printf("|%4f   %4f   %7f|\n", consumtion.wind, consumtion.hydro, consumtion.biomass);*/
}
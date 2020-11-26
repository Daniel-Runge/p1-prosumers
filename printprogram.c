#include <stdio.h>
/**
     * @brief a welcome message in the making, this is just an outcast
     * 
     */
void welcomeprint();
void printdata();
/**
 * @brief Use struct for printing data, use output from analyze to print the evaluation.

 use array of strings or switch to store the potential analysis results.
 * 
 * @return int 
 */
const char *co2[] = {
    "Right now the energy in denmark is green\n",
    "The energy in Denmark is not green right now\n"};
int main(void)
{
    welcomeprint();
    printdata();
    return (0);
}
/**
 * @brief It is not finished
 * 
 */
void welcomeprint()
{
    printf("Hello love, welcome to our energy data program. This program can show you how Denmark "
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
void printdata()
{
    int wind =193, hydro =34, biomass =34, sum, procent = 48, intensitet = 86;
    sum = wind + hydro + biomass;

    printf("Right now the procent of renewable energy in Denmark is %d\n",procent);
    printf("The carbon intensity in Denmark is %d (kilde eller noget)\n", intensitet);

    printf("So the conclusion must be \n%s\n",co2[0]);
    printf("The total amount of energy in Denmark is produced by\n");
    printf("|Wind     Hydro     Biomass     Sum|\n");
    printf("|%4d   %4d   %7d   %10d|\n", wind, hydro, biomass, sum);
}
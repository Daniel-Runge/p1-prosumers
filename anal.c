#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    double renewable;
    double wind;
    double biomass;
    double solar;
    double hydro;
    double PowerConsumtion;
}data;

/*Main*/

int main ()
{
    data api;
    double wind_procentage, hydro_procentage, biomass_procentage; 
    int sum;

    api.renewable = 91;
    api.biomass = 207;
    api.solar = 0;
    api.hydro = 848;
    api.wind = 1900;
    api.PowerConsumtion = 3237;

    wind_procentage = api.wind / api.PowerConsumtion * 100;
    hydro_procentage =  api.hydro / api.PowerConsumtion * 100;
    biomass_procentage = api.biomass / api.PowerConsumtion * 100;

    printf("Wind:     %6.2lf %%\n", wind_procentage);
    printf("Hydro:    %6.2lf %%\n", hydro_procentage);
    printf("Biomass:  %6.2lf %%\n", biomass_procentage);
    printf("Sum:      %6d %%\n", sum = wind_procentage + hydro_procentage + biomass_procentage);


    return 0;
}


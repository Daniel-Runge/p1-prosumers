#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct /*Data we get from the API in MW |POWER CONSUMTION STRUCT|*/
{
    double battery_discharge;
    double biomass;
    double coal;
    double gas;
    double hydro;
    double hydro_discharge;
    double nuclear;
    double oil;
    double solar;
    double wind;
    double geothermal;
    double unknown;   
}data_consumtion;

typedef struct /*Data we get from the API in MW |TOTAL SECTION|*/
{
    double fossile;
    double renewable;
    double consumtionTotal;
    double productionTotal;
    double ImportTotal;
    double ExportTotal;
}data_total;

/**
 * @brief Function to analyze data that comes from the API.
 * 
 * @param total The data from the APIs Total section.
 * @param consumtion The data from the APIs consumtion section.
 * @return int To to use for the final print statement.
 */

int analyze_data(data_total total, data_consumtion consumtion)
{
    data_consumtion consumtion;
    data_total total;
    double wind_procentage, hydro_procentage, biomass_procentage; 
    int sum;
    

    /*Data that was taken from an API Request |NOT UP TO DATE|*/
    total.fossile = 91;
    total.renewable = 91;
    total.consumtionTotal = 3237;

    consumtion.biomass = 207;
    consumtion.solar = 0;
    consumtion.hydro = 848;
    consumtion.wind = 1900;


    wind_procentage = consumtion.wind / total.consumtionTotal * 100; /*Precentage of total prower from wind*/
    hydro_procentage =  consumtion.hydro / total.consumtionTotal * 100; /*Precentage of total prower from Hydro*/
    biomass_procentage = consumtion.biomass / total.consumtionTotal * 100; /*Precentage of total prower from Biomass*/

    printf("Wind:     %6.2lf %%\n", wind_procentage);
    printf("Hydro:    %6.2lf %%\n", hydro_procentage);
    printf("Biomass:  %6.2lf %%\n", biomass_procentage);
    printf("Sum:      %6d %%\n", sum = wind_procentage + hydro_procentage + biomass_procentage);

    /*How much CO2 in grams the different types of energy make in kWh (Kilo Watt Hour)*/
    /*1 MW = 1000 kWh*/
    /*Wind 11 gCO2/kWh*/
    /*Hydro 24 gCO2/kWh*/
    /*Solar 45 gCO2/kWh*/
    /*Biomass 230 gCO2/kWh*/
    /*Coal 820 gCO2/kWh*/


    




    return 0;
}


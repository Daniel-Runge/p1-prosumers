#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "energyAppFunctions.h"

int analyze_data(DataStats total, DataConsumption consumption);
int green_power(DataStats *value);
int wind_power(DataStats total, DataConsumption consumption);

/**
 * @brief Function to analyze data that comes from the API.
 * 
 * @param total The data from the APIs Total section.
 * @param consumption The data from the APIs consumption section.
 * @return int To to use for the final print statement.
 */

/* int main()
{
    DataConsumption consumption;
    DataStats total;


    total.carbonIntensity = 200;

    total.fossile = 73;
    total.renewable = 71;
    total.consumptionTotal = 2807;

    consumption.biomass = 197;
    consumption.coal = 485;
    consumption.gas = 179;
    consumption.hydro = 951;
    consumption.hydro_discharge = 60;
    consumption.nuclear = 68;
    consumption.oil = 10;
    consumption.solar = 74;
    consumption.wind = 763;
    consumption.geothermal = 0;
    consumption.unknown = 20;


    analyze_data(total, consumption);

    wind_power(total, consumption);

    printf("%d\n", wind_power(total, consumption));

    return 0;
} */

/**
 * @brief A function for futher use of analyzing data in the future.
 * 
 * @param total API DATA
 * @param consumption API DATA
 * @return int Analyzed data returned to print.
 */

int analyze_data(DataStats total, DataConsumption consumption)
{
    double wind_procentage, hydro_procentage, biomass_procentage, solar_procentage, hydro_dischare_procentage;
    double renewable_sum;

    solar_procentage = (consumption.solar * 100.) / total.consumptionTotal;
    wind_procentage = (consumption.wind * 100.) / total.consumptionTotal;       /*Precentage of total prower from wind*/
    hydro_procentage = (consumption.hydro * 100.) / total.consumptionTotal;     /*Precentage of total prower from Hydro*/
    biomass_procentage = (consumption.biomass * 100.) / total.consumptionTotal; /*Precentage of total prower from Biomass*/

    printf("Solar:            %6.2lf %%\n", solar_procentage);
    printf("Wind:             %6.2lf %%\n", wind_procentage);
    printf("Hydro:            %6.2lf %%\n", hydro_procentage);
    printf("Biomass:          %6.2lf %%\n", biomass_procentage);
    printf("Sum af renewable: %6.2f %%\n", renewable_sum = wind_procentage + hydro_procentage + biomass_procentage + solar_procentage);



    /*How much CO2 in grams the different types of energy make in kWh (Kilo Watt Hour)*/
    /*1 MW = 1000 kWh*/
    /*Wind 11 gCO2/kWh*/
    /*Hydro 24 gCO2/kWh*/
    /*Solar 45 gCO2/kWh*/
    /*Biomass 230 gCO2/kWh*/
    /*Coal 820 gCO2/kWh*/

    return 1;
}

/**
 * 
 * @brief Function to get the index for the print statement is the power green?
 * 
 * @param value The intensity struct as a pointer with the green value returen in the struct.
 * @return int Returns the 
 */

int GreenPower(DataStats *value)
{
    if (value->carbonIntensity <= 100)
    {
        return 0;
    }
    else if (value->carbonIntensity <= 200)
    {
        return 1;
    }
    else if (value->carbonIntensity <= 300)
    {
        return 2;
    }
    else
    {
        return 3;
    }
}

/**
 * @brief A function to show if the wind is strong or not.
 * 
 * @param total Data from the total section of the API.
 * @param consumption Data from the consumption section of the API.
 * @return int Return 1 if wind power is 10% or under 2 if its over 50% and 0 if its anything else.
 */

int wind_power(DataStats total, DataConsumption consumption)
{
    int wind_procentage;
    wind_procentage = (consumption.wind * 100.) / total.consumptionTotal;

    if (wind_procentage <= 10)
    {
        return 1;
    }
    else if (wind_procentage >= 50)
    {
        return 2;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief |WORK IN PROGRESS|
 * 
 * @param total 
 * @param consumption 
 * @return int 
 */

int coal_power(DataStats total, DataConsumption consumption) 
{
    int coal_procentage;
    coal_procentage = (consumption.coal * 100.) / total.consumptionTotal;

    if (coal_procentage >= 20)
    {
        return 1;
    }
    else if (coal_procentage <= 10)
    {
        return 2;
    }
    else
    {
        return 0;
    }
}


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "energyAppFunctions.h"

int analyze_data(data_total total, data_consumtion consumtion);
int green_power(data_total *value);
int wind_power(data_total total, data_consumtion consumtion);

/**
 * @brief Function to analyze data that comes from the API.
 * 
 * @param total The data from the APIs Total section.
 * @param consumtion The data from the APIs consumtion section.
 * @return int To to use for the final print statement.
 */

int main()
{
    data_consumtion consumtion;
    data_total total;

    /*Dummy data*/

    total.carbon_intensity = 200;

    /*Data that was taken from an API Request |NOT UP TO DATE|*/
    total.fossile = 73;
    total.renewable = 71;
    total.consumtionTotal = 2807;

    consumtion.biomass = 197;
    consumtion.coal = 485;
    consumtion.gas = 179;
    consumtion.hydro = 951;
    consumtion.hydro_discharge = 60;
    consumtion.nuclear = 68;
    consumtion.oil = 10;
    consumtion.solar = 74;
    consumtion.wind = 763;
    consumtion.geothermal = 0;
    consumtion.unknown = 20;

    /*green_power(&total);*/

    analyze_data(total, consumtion);

    wind_power(total, consumtion);

    printf("%d\n", wind_power(total, consumtion));

    return 0;
}

/**
 * @brief A function for futher use of analyzing data in the future.
 * 
 * @param total API DATA
 * @param consumtion API DATA
 * @return int Analyzed data returned to print.
 */

int analyze_data(data_total total, data_consumtion consumtion)
{
    double wind_procentage, hydro_procentage, biomass_procentage, solar_procentage, hydro_dischare_procentage;
    double renewable_sum;

    solar_procentage = (consumtion.solar * 100.) / total.consumtionTotal;
    wind_procentage = (consumtion.wind * 100.) / total.consumtionTotal;       /*Precentage of total prower from wind*/
    hydro_procentage = (consumtion.hydro * 100.) / total.consumtionTotal;     /*Precentage of total prower from Hydro*/
    biomass_procentage = (consumtion.biomass * 100.) / total.consumtionTotal; /*Precentage of total prower from Biomass*/

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

int green_power(data_total *value)
{
    if (value->carbon_intensity <= 100)
    {
        return 0;
    }
    else if (value->carbon_intensity <= 200)
    {
        return 1;
    }
    else if (value->carbon_intensity <= 300)
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
 * @param consumtion Data from the consumtion section of the API.
 * @return int Return 1 if wind power is 10% or under 2 if its over 50% and 0 if its anything else.
 */

int wind_power(data_total total, data_consumtion consumtion)
{
    int wind_procentage;
    wind_procentage = (consumtion.wind * 100.) / total.consumtionTotal;

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
 * @param consumtion 
 * @return int 
 */

int coal_power(data_total total, data_consumtion consumtion) 
{
    int coal_procentage;
    coal_procentage = (consumtion.coal * 100.) / total.consumtionTotal;

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


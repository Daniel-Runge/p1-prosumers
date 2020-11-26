#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct /*Data we get from the API in MW |POWER CONSUMTION STRUCT|*/
{
    int battery_discharge;
    int biomass;
    int coal;
    int gas;
    int hydro;
    int hydro_discharge;
    int nuclear;
    int oil;
    int solar;
    int wind;
    int geothermal;
    int unknown;
} data_consumtion;

typedef struct /*Data we get from the API in MW |TOTAL SECTION|*/
{
    int fossile;
    int renewable;
    int consumtionTotal;
    int productionTotal;
    int ImportTotal;
    int ExportTotal;
} data_total;

typedef struct
{
    int carbon;
    int green;
}intensity;


int analyze_data(data_total total, data_consumtion consumtion);
void green_power(intensity *value);

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
    intensity value;

    /*Dummy data*/

    value.carbon = 200;

    /*Data that was taken from an API Request |NOT UP TO DATE|*/
    total.fossile = 91;
    total.renewable = 91;
    total.consumtionTotal = 3237;

    consumtion.biomass = 207;
    consumtion.solar = 0;
    consumtion.hydro = 848;
    consumtion.wind = 1900;

    analyze_data(total, consumtion);

    green_power(&value);

    return 0;
}

int analyze_data(data_total total, data_consumtion consumtion)
{
    double wind_procentage, hydro_procentage, biomass_procentage;
    int sum;

    wind_procentage = (consumtion.wind * 100.) / total.consumtionTotal;       /*Precentage of total prower from wind*/
    hydro_procentage = (consumtion.hydro * 100.) / total.consumtionTotal;     /*Precentage of total prower from Hydro*/
    biomass_procentage = (consumtion.biomass * 100.) / total.consumtionTotal; /*Precentage of total prower from Biomass*/

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

    return 1;
}

void green_power(intensity *value)
{
    if (value->carbon <= 100)
    {
        value->green = 0;
    }
    else if (value->carbon <= 200)
    {
        value->green = 1;
    }
    else if (value->carbon <= 300)
    {
        value->green = 2;
    }
}


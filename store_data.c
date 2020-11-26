/*
* Vi læser data
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <json-c/json.h>

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
} data_consumtion;

typedef struct /*Data we get from the API in MW |TOTAL SECTION|*/
{
    double fossile;
    double renewable;
    double consumtionTotal;
    double productionTotal;
    double ImportTotal;
    double ExportTotal;
    double carbon_intensity;
} data_total;

int EnergyParser(char *Filename, char *KeyWord);

/**
 * @brief Copypaste work so far
 * Will be adjusted so it can scan data into our struct
 * Everything above will be deleted when integrated into the program
 * 
 * @return type is int because it's the main function right now
 */
int main(void)
{
    int i, j;
    data_total POWAH;
    char *KeyWord[] = {"battery discharge", "biomass", "coal", "gas", "hydro", 
    "hydro discharge", "nuclear", "oil", "solar", "wind", "geothermal", "unknown", 
    "fossilFreePercentage", "renewablePercentage", "powerConsumptionTotal", 
    "powerProductionTotal", "powerImportTotal", "powerExportTotal", "carbonIntensity"};

    char *Filename[] = {"renewable_dk1.json", "renewable_dk2.json", 
    "carbon_intensity_dk1.json", "carbon_intensity_dk2.json"};

    POWAH.renewable = EnergyParser(Filename[0], KeyWord[13]);
    POWAH.carbon_intensity = EnergyParser(Filename[2], KeyWord[18]);
    printf("Renewable: %lf \nCarbon: %lf\n", POWAH.renewable, POWAH.carbon_intensity);
    return(0);
}

int EnergyParser(char *Filename, char *KeyWord)
{
    FILE *fp;
    char FileBuffer[1800];
    struct json_object *Full_json;
    struct json_object *Consumption;
    struct json_object *PowerSource;
    fp = fopen(Filename, "r");
    if (fp == NULL)
    {
        printf("Could not read JSON file\n");
    }
    fread(FileBuffer, 1800, 1, fp);
    fclose(fp);

    Full_json = json_tokener_parse(FileBuffer);
    json_object_object_get_ex(Full_json, KeyWord, &PowerSource);
    if (json_object_get_int(PowerSource) == 0)
    {
        json_object_object_get_ex(Full_json, "powerConsumptionBreakdown", &Consumption);
        json_object_object_get_ex(Consumption, KeyWord, &PowerSource);
    }
    printf("%s: %d\n", KeyWord, json_object_get_int(PowerSource));
    return (double)json_object_get_int(PowerSource);
}

#include <stdio.h>
#include <json-c/json.h>
#include "energyAppFunctions.h"

double EnergyParser(char *Filename, char *KeyWord);
void readFile(data_total *data);

/**
 * @brief Function takes the created files by api_download.c and runs thorugh them looking
 * for the data we need using certain words.
 * The KeyWord array is for future development.
 */

void readFile(data_total *data)
{
    char *KeyWord[] = {"battery discharge", "biomass", "coal", "gas", "hydro", 
    "hydro discharge", "nuclear", "oil", "solar", "wind", "geothermal", "unknown", 
    "fossilFreePercentage", "renewablePercentage", "powerConsumptionTotal", 
    "powerProductionTotal", "powerImportTotal", "powerExportTotal", "carbonIntensity"};

    char *Filename[] = {"renewable.json", "carbonIntensity.json"};

    data->renewable = EnergyParser(Filename[0], KeyWord[13]);
    data->carbon_intensity = EnergyParser(Filename[1], KeyWord[18]);
}

/**
 * @brief Reads a json file, searches for the keyword. If no keyword is found,
 * it tries searching in the powerConsumptionTotal part of the json.
 * 
 * @return is made with the json-c library to parse the file and return the corresponding data.
 * 
 */
double EnergyParser(char *Filename, char *KeyWord)
{
    FILE *fp;
    char FileBuffer[1800];
    struct json_object *Full_json;
    struct json_object *Consumption;
    struct json_object *FoundNumber;
    fp = fopen(Filename, "r");
    if (fp == NULL)
    {
        printf("Could not read file\n");
    }
    fread(FileBuffer, 1800, 1, fp);
    fclose(fp);

    Full_json = json_tokener_parse(FileBuffer);
    json_object_object_get_ex(Full_json, KeyWord, &FoundNumber);
    if (json_object_get_int(FoundNumber) == 0)
    {
        json_object_object_get_ex(Full_json, "powerConsumptionBreakdown", &Consumption);
        json_object_object_get_ex(Consumption, KeyWord, &FoundNumber);
    }
    return (json_object_get_int(FoundNumber));
}
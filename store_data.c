/*
* Vi læser data
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <json-c/json.h>
#include "energyAppFunctions.h"

double EnergyParser(char *Filename, char *KeyWord);
void readFile(data_total *POWAH);

/**
 * @brief Function takes the created files by the API and runs thorugh them checking
 * for certain words that we need.
 * Massive @KeyWord array is for future development in case that would be nice to have
 * After finding the @KeyWord, the function takes the following integer
 * and places it into a struct variable that fits.
 * 
 * @return type is void.
 */

void readFile(data_total *POWAH)
{
    char *KeyWord[] = {"battery discharge", "biomass", "coal", "gas", "hydro", 
    "hydro discharge", "nuclear", "oil", "solar", "wind", "geothermal", "unknown", 
    "fossilFreePercentage", "renewablePercentage", "powerConsumptionTotal", 
    "powerProductionTotal", "powerImportTotal", "powerExportTotal", "carbonIntensity"};

    char *Filename[] = {"renewable_dk1.json", "renewable_dk2.json", 
    "carbon_intensity_dk1.json", "carbon_intensity_dk2.json"};

    POWAH->renewable = EnergyParser(Filename[0], KeyWord[13]);
    POWAH->carbon_intensity = EnergyParser(Filename[2], KeyWord[18]);
}

/**
 * @brief Reads a json file, searches for the keyword. If no keyword is found,
 * it tries searching in the powerConsumptionTotal part of the json.
 * 
 * @param Filename is one of four files created by api_download.c 
 * that will be looked thorugh.
 * @param KeyWord is a word in the json file, which will indicate that the
 * following number should be picked up by the function.
 * @return double is the found number after the keyword.
 */
double EnergyParser(char *Filename, char *KeyWord)
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
    return (json_object_get_int(PowerSource));
}
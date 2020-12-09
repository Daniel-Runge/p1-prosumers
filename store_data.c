
#include <stdio.h>
#include <json-c/json.h>
#include "energyAppFunctions.h"

double EnergyParser(char *filename, char *keyword);
void PrepareParsing(DataStats *data);
void WeatherParser(char *filename, WindData windPower[]);

/**
 * @brief Function takes the created files by api_download.c and runs thorugh them looking
 * for the data we need using certain words.
 * The keyword array is for future development.
 */

void PrepareParsing(DataStats *data)
{
    char *keyword[] = {"battery discharge", "biomass", "coal", "gas", "hydro", 
    "hydro discharge", "nuclear", "oil", "solar", "wind", "geothermal", "unknown", 
    "fossilFreePercentage", "renewablePercentage", "powerConsumptionTotal", 
    "powerProductionTotal", "powerImportTotal", "powerExportTotal", "carbonIntensity"};

    char *filename[] = {"renewable.json", "carbonIntensity.json"};

    data->renewable = EnergyParser(filename[0], keyword[13]);
    data->carbonIntensity = EnergyParser(filename[1], keyword[18]);
}

/**
 * @brief Reads a json file, searches for the keyword. If no keyword is found,
 * it tries searching in the powerConsumptionTotal part of the json.
 * 
 * @return is made with the json-c library to parse the file and return the corresponding data.
 * 
 */
double EnergyParser(char *filename, char *keyword)
{
    FILE *fp;
    char fileBuffer[1800];
    struct json_object *fullJson;
    struct json_object *consumption;
    struct json_object *foundNumber;
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Could not read file\n");
    }
    fread(fileBuffer, 1800, 1, fp);
    fclose(fp);

    fullJson = json_tokener_parse(fileBuffer);
    json_object_object_get_ex(fullJson, keyword, &foundNumber);
    if (json_object_get_int(foundNumber) == 0)
    {
        json_object_object_get_ex(fullJson, "powerConsumptionBreakdown", &consumption);
        json_object_object_get_ex(consumption, keyword, &foundNumber);
    }
    return (json_object_get_int(foundNumber));
}

/**
 * @brief Takes a json file and parses it for our wanted data(Time and windspeed). 
 * The data is then put into the WindPower struct.
 * 
 * @param filename is the name of the file which we need to open and parse.
 */
void WeatherParser(char *filename, WindData windPower[])
{
    FILE *fp;
    char fileBuffer[15000];
    int i, numOfHours;
    struct json_object *fullJson;
    struct json_object *allHours;
    struct json_object *singleHour;
    struct json_object *time;
    struct json_object *wind;
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Could not read weather JSON file\n");
    }
    fread(fileBuffer, 15000, 1, fp);
    fclose(fp);

    fullJson = json_tokener_parse(fileBuffer);
    json_object_object_get_ex(fullJson, "hourly", &allHours);
    numOfHours = json_object_array_length(allHours);
    for (i = 0; i < numOfHours; i++)
    {
        singleHour = json_object_array_get_idx(allHours, i);
        json_object_object_get_ex(singleHour, "dt", &time);
        json_object_object_get_ex(singleHour, "wind_speed", &wind);
        windPower[i].unixTime = json_object_get_int(time);
        windPower[i].windSpeed = json_object_get_double(wind);
    }
}
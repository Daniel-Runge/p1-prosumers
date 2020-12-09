
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
    data->carbon_intensity = EnergyParser(Filename[0], KeyWord[18]);
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
        printf("Could not read GUSTAV file\n");
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

/**
 * @brief Takes a json file and parses it for our wanted data(Time and windspeed). 
 * The data is then put into the WindPower struct.
 * 
 * @param Filename is the name of the file which we need to open and parse.
 */
void WeatherParser(char *Filename, WindData WindPower[])
{
    FILE *fp;
    char FileBuffer[15000];
    int i, NumOfHours;
    struct json_object *Full_json;
    struct json_object *AllHours;
    struct json_object *SingleHour;
    struct json_object *Time;
    struct json_object *Wind;
    /*Opens file, reads data and puts data in 'FileBuffer'*/
    fp = fopen(Filename, "r");
    if (fp == NULL)
    {
        printf("Could not read weather JSON file\n");
    }
    fread(FileBuffer, 15000, 1, fp);
    fclose(fp);

    /*Takes FileBuffer and puts it in Full_json struct, so it now is a json_object*/
    Full_json = json_tokener_parse(FileBuffer);
    /*Looks for 'hourly' from json file and puts 'hourly' array into the 'AllHours' json_object*/
    json_object_object_get_ex(Full_json, "hourly", &AllHours);
    /*Gives us the amount of hours we have forecasts for*/
    NumOfHours = json_object_array_length(AllHours);
    printf("%d\n", NumOfHours);
    /*for-loop puts data from every hour in correct place in the WindPower struct
    unixTime = Time
    WindSpeed = Wind*/
    for (i = 0; i < NumOfHours; i++)
    {
        SingleHour = json_object_array_get_idx(AllHours, i);
        json_object_object_get_ex(SingleHour, "dt", &Time);
        json_object_object_get_ex(SingleHour, "wind_speed", &Wind);
        WindPower[i].UnixTime = json_object_get_int(Time);
        WindPower[i].WindSpeed = json_object_get_double(Wind);
    }
}
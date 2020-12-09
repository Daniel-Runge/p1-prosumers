#include <time.h>

/**
 * @brief Struct to contain CONSUMPTION data from Electricity Map API
 * 
 */
typedef struct 
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
} data_consumption;

/**
 * @brief Struct to contain CARBON INTENSITY data from Electricity Map API
 * 
 */
typedef struct 
{
    double fossile;
    double renewable;
    double consumptionTotal;
    double productionTotal;
    double ImportTotal;
    double ExportTotal;
    double carbon_intensity;
} data_total;

/**
 * @brief Struct to contain the user settings determining how the program handles output
 * 
 */
typedef struct
{
    char location;
    int forecast;
    int numberOfHours;
    int CO2Intensity;
} settings;

/**
 * @brief Data to contain WIND and TIME data pairs from openweathermap
 * 
 */
typedef struct
{
    time_t UnixTime;
    double WindSpeed;
} WindData;

/**
 * @brief Struct to contain a certain point in time.
 * 
 */
typedef struct
{
    long int sec;
    long int min;
    long int hour;
    long int day;
} TimeInfo;

/**
 * prototypes from the energyApp.c file
 */
void EnergiApp(void);
/**
 * prototypes from the command.c file
 */
char Command (settings settings);

/**
 * prototypes from the api_download.c file
 */
void fileMaker(char Location);
void get_api (char* filemode, char* url, char* filename, char* auth);

/**
 * prototypes from the store_data.c file
 */
void readFile(data_total *POWAH);
double EnergyParser(char *Filename, char *KeyWord);
void WeatherParser(char *Filename, WindData WindPower[]);

/**
 * prototypes from the analyze.c file
 */
int green_power(data_total *value);

/**
 * prototypes from the printprogram.c file
 */
void welcomeprint();
void printdata(data_total total, data_consumption consumption, settings settings);
void Plot(WindData WindPower[], int MaxHours);

/**
 * Prototypes from HandleSettings.c 
 */
int CheckSettings();
settings CreateSettings();
void UpdateSettingsFile(settings settings);
void UpdateSettingsMenu(settings settings);
void UpdateSetting(settings *settings, char command);

/**
 * Prototypes from HandleInput.c
 */
int ValidateCharInput(char candidate, char option1, char option2);
char CharInput (void);
int IntInput(void);
void CleanStdin();

/**
 * Prototypes from WeatherPrint.c
 */
void TimeForWind(WindData WindPower[50], int hoursAhead, TimeInfo *InfoTime);
void ConvertUnixDate(time_t unix_number);
void SecondsConverter(long int sekunder, TimeInfo *TimeInfo);
int CompareWindSpeed(const void *a, const void *b);
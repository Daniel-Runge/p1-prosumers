
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
} data_consumption;

typedef struct /*Data we get from the API in MW |TOTAL SECTION|*/
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
 * @brief Settings struct to determine the handling of data.
 * 
 */
typedef struct
{
    char location;
    int forecast;
    int numberOfHours;
    int CO2Intensity;
} settings;

typedef struct
{
    time_t UnixTime;
    double WindSpeed;
} WindData;

typedef struct
{
    long int sec;
    long int min;
    long int hour;
    long int day;
} TimeInfo;

/**
 * @brief prototypes from the energyApp.c file
 */
void EnergiApp(void);
/**
 * @brief prototypes from the command.c file
 */
char Command (settings settings);

/**
 * @brief prototypes from the api_download.c file
 */
void fileMaker(char Location);
void get_api (char* filemode, char* url, char* filename, char* auth);

/**
 * @brief prototypes from the store_data.c file
 */
void readFile(data_total *POWAH);
double EnergyParser(char *Filename, char *KeyWord);

/**
 * @brief prototypes from the analyze.c file
 */
int green_power(data_total *value);

/**
 * @brief prototypes from the printprogram.c file
 */
void welcomeprint();
void printdata(data_total total, data_consumption consumption, int parameter);

/**
 * @brief Prototypes from HandleSettings.c 
 */
int CheckSettings();
settings CreateSettings();
void UpdateSettingsFile(settings settings);
void UpdateSettingsMenu(settings settings);
void UpdateSetting(settings *settings, char command);

/**
 * @brief Prototypes from HandleInput.c
 */
int ValidateCharInput(char candidate, int num, ...);
char CharInput (void);
int IntInput(void);
void CleanStdin();

/**
 * @brief Prototypes from WeatherPrint.c
 */
void TimeForWind(WindData WindPower[50], int hoursAhead, TimeInfo *InfoTime);
void ConvertUnixDate(time_t unix_number);
void SecondsConverter(long int sekunder, TimeInfo *TimeInfo);
int CompareWindSpeed(const void *a, const void *b);

/**
 * @brief Prototypes from Forecast.c
 */
void Plot(WindData WindPower[], int MaxHours);
void WeatherParser(char *Filename);
void get_api(char *filemode, char *url, char *filename, char *auth);
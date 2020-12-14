#include <time.h>


/**
 * @brief Struct to contain CARBON INTENSITY data from Electricity Map API
 * 
 */
typedef struct 
{
    double renewable;
    double carbonIntensity;
} DataStats;

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
    int plot;
} Settings;

/**
 * @brief Data to contain WIND and TIME data pairs from openweathermap
 * 
 */
typedef struct
{
    time_t unixTime;
    double windSpeed;
} WindData;

/**
 * @brief Struct to contain a certain point in time.
 * 
 */
typedef struct
{
    int sec;
    int min;
    int hour;
    int day;
} TimeSplit;

/**
 * prototypes from the energyApp.c file
 */
void EnergyApp(void);

/**
 * prototypes from the api_download.c file
 */
void GetApiFiles(char location);
void ContactApi(char* filemode, char* url, char* filename, char* auth);

/**
 * prototypes from the store_data.c file
 */
void PrepareParsing(DataStats *data);
double EnergyParser(char *filename, char *keyWord);
void WeatherParser(char *filename, WindData windPower[]);

/**
 * prototypes from the analyze.c file
 */
int GreenPower(DataStats *value);

/**
 * prototypes from the printprogram.c file
 */
void WelcomePrint();
void PrintData(DataStats total, Settings settings, WindData windpower[], WindData sortedWinds[]);

/**
 * Prototypes from HandleSettings.c 
 */
int CheckSettings(void);
Settings CreateSettings(void);
void UpdateSettingsFile(Settings settings);
void UpdateSettingsMenu(Settings *settings);
void UpdateSetting(Settings *settings, char command);
void CreateSettingsStruct(Settings *settings);
void SettingsInstructions(void);

/**
 * Prototypes from HandleInput.c
 */
int ValidateCharInput(char candidate, char option1, char option2);
char GetUserCharInput (void);
int GetUserIntInput(void);
void CleanStandardInput();
char Command (Settings *settings);

/**
 * Prototypes from WeatherPrint.c
 */
void GetBestTimeForWind(WindData windPower[50], int hoursAhead, TimeSplit *InfoTime, WindData sortedWinds[]);
void ConvertUnixDate(time_t unixNumber);
int CompareWindSpeed(const void *a, const void *b);
void PlotForecast(WindData windPower[], int maxHours);
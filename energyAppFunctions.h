
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
    int green;
} settings;

/**
 * @brief prototypes from the energyApp.c file
 */
void EnergiApp(void);
/**
 * @brief prototypes from the command.c file
 */
char Command (void);

/**
 * @brief prototypes from the api_download.c file
 */
int fileMaker(void);
void get_api (char* filemode, char* url, char* filename);

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
settings CreateSettingsStruct();
void UpdateSettingsFile(settings settings);
void UpdateSettingsStruct();

/**
 * @brief Prototypes from HandleInput.c
 */
int ValidateInput(char candidate, char option1, char option2);
char CharInput (void);
int IntInput(void);
int clean_stdin();
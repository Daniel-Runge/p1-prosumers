#include <stdio.h>
#include "energyAppFunctions.h"

#define SETTINGS_FILE "settings.txt"
#define ERROR_FILE "Could not open the file %s\n"
#define ERROR_SCAN_RETRY "Invalid input! Try again\n"

/**
 * @brief Function to determine existence of settings.txt file.
 * 
 * @return 1 if the settings file exists. 0 if it does not exist.
 */
int CheckSettings()
{
    FILE *settingsFile = fopen(SETTINGS_FILE, "r");
    if (settingsFile == NULL)
    {
        return 0;
    }
    return 1;
}

/**
 * @brief Create a Settings Struct object
 * 
 * @return settings 
 */
settings CreateSettingsStruct()
{
    settings settings;
    char charBuffer;
    int intBuffer;

    printf("No settings detected, creating user settings:\n"
    "Are you in w(est) or e(ast)?\n");
    charBuffer = CharInput();
    while(!ValidateCharInput(charBuffer, 'w', 'e')){
        printf(ERROR_SCAN_RETRY);
        charBuffer = CharInput();
    }
    settings.location = charBuffer;

    printf("Do you wish to see a forecast? (y/n)\n");
    charBuffer = CharInput();
    while(!ValidateCharInput(charBuffer, 'y', 'n')){
        printf(ERROR_SCAN_RETRY);
        charBuffer = CharInput();
    }
    settings.forecast = charBuffer == 'y' ? 1 : 0;

    settings.numberOfHours = 0;
    if(settings.forecast){
        printf("How many hours do you wish to compare? (1-48)\n");
        intBuffer = IntInput();
        while(intBuffer > 48 || intBuffer < 1){
            printf(ERROR_SCAN_RETRY);
            intBuffer = IntInput();
        }
    }
    settings.numberOfHours = intBuffer;

    printf("Do you wish us to evaluate if the energy is green right now? (y/n)\n");
    charBuffer = CharInput();
    while(!ValidateCharInput(charBuffer, 'y', 'n')){
        printf(ERROR_SCAN_RETRY);
        charBuffer = CharInput();
    }
    settings.green = charBuffer == 'y' ? 1 : 0;

    return settings;
}

/**
 * @brief Update the settings file based on the settings struct.
 * 
 * @param settings 
 */
void UpdateSettingsFile(settings settings)
{
    FILE *settingsFile = fopen(SETTINGS_FILE, "w");

    if (settingsFile == NULL)
    {
        printf(ERROR_FILE, SETTINGS_FILE);
    }
    fprintf(settingsFile, "%c", settings.location);
    fprintf(settingsFile, "\n%d", settings.forecast);
    fprintf(settingsFile, "\n%d", settings.numberOfHours);
    fprintf(settingsFile, "\n%d", settings.green);

    fclose(settingsFile);
}
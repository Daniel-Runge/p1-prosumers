#include <stdio.h>
#include "energyAppFunctions.h"

#define SETTINGS_FILE "settings.txt"
#define ERROR_FILE "Could not open the file %s\n"
#define ERROR_SCAN_RETRY "Invalid input! Try again\n"
#define SETTINGS_WELCOME_MESSAGE "This is the settings menu.\n" \
                                 "The current settings: Location - %c, CO2 Intensity - %c, Forecast - %c"

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
    fclose(settingsFile);
    return 1;
}

/**
 * @brief Create a Settings Struct object
 * 
 * @return settings 
 */
Settings CreateSettings()
{
    Settings settings;
    char charBuffer;
    int intBuffer;

    printf("No settings detected, creating user settings:\n"
           "Are you in w(est) or e(ast)?\n");
    charBuffer = GetUserCharInput();
    while (!ValidateCharInput(charBuffer, 'w', 'e'))
    {
        printf(ERROR_SCAN_RETRY);
        charBuffer = GetUserCharInput();
    }
    settings.location = charBuffer;

    printf("Do you wish to see a forecast? (y/n)\n");
    charBuffer = GetUserCharInput();
    while (!ValidateCharInput(charBuffer, 'y', 'n'))
    {
        printf(ERROR_SCAN_RETRY);
        charBuffer = GetUserCharInput();
    }
    settings.forecast = charBuffer == 'y' ? 1 : 0;

    settings.numberOfHours = 0;
    if (settings.forecast)
    {
        printf("How many hours do you wish to compare? (1-48)\n");
        intBuffer = GetUserIntInput();
        while (intBuffer > 48 || intBuffer < 1)
        {
            printf(ERROR_SCAN_RETRY);
            intBuffer = GetUserIntInput();
        }
    }
    settings.numberOfHours = intBuffer;

    printf("Do you wish to see the specific CO2 intensity? (y/n)\n");
    charBuffer = GetUserCharInput();
    while (!ValidateCharInput(charBuffer, 'y', 'n'))
    {
        printf(ERROR_SCAN_RETRY);
        charBuffer = GetUserCharInput();
    }
    settings.CO2Intensity = charBuffer == 'y' ? 1 : 0;

    UpdateSettingsFile(settings);
    return settings;
}
void CreateSettingsStruct(Settings *settings)
{
    FILE *settingsFile;
    settingsFile = fopen(SETTINGS_FILE, "r");
    if (settingsFile == NULL)
    {
        printf(ERROR_FILE, SETTINGS_FILE);
    }
    fscanf(settingsFile," %c",&settings->location);
    fscanf(settingsFile,"%d",&settings->forecast);
    fscanf(settingsFile,"%d",&settings->numberOfHours);
    fscanf(settingsFile,"%d",&settings->CO2Intensity);
    fclose(settingsFile);
}
/**
 * @brief Update the settings file based on the settings struct.
 * 
 * @param settings 
 */
void UpdateSettingsFile(Settings settings)
{
    FILE *settingsFile = fopen(SETTINGS_FILE, "w");

    if (settingsFile == NULL)
    {
        printf(ERROR_FILE, SETTINGS_FILE);
    }
    fprintf(settingsFile, "%c", settings.location);
    fprintf(settingsFile, "\n%d", settings.forecast);
    fprintf(settingsFile, "\n%d", settings.numberOfHours);
    fprintf(settingsFile, "\n%d", settings.CO2Intensity);

    fclose(settingsFile);
}

void UpdateSettingsMenu(Settings settings)
{
    char choice;
    printf(SETTINGS_WELCOME_MESSAGE,
           settings.location, settings.CO2Intensity, settings.forecast);
    if (settings.forecast)
    {
        printf(" Forecast hours - %d", settings.numberOfHours);
    }
    puts("\n");

    printf("Write -l to change to location,\n"
           "-c to change CO2 intensity,\n"
           "-f to change forecast,\n"
           "-h to change the number of hours,\n"
           "-e to exit settings menu.\n");

    do{
        choice = GetUserCharInput();
        UpdateSetting(&settings, choice);
    }while(choice != 'e');
}

/**
 * @brief Update a single setting in the struct and file.
 * 
 * @param settings 
 * @param command 
 */
void UpdateSetting(Settings *settings, char command)
{
    switch (command)
    {
    case 'l':
        settings->location = settings->location == 'e' ? 'w' : 'e';
        break;
    case 'c':
        settings->CO2Intensity = settings->CO2Intensity == 1 ? 0 : 1;
        break;
    case 'f':
        settings->forecast = settings->forecast == 1 ? 0 : 1;
        break;
    case 'h':
        if (settings->forecast)
        {
            settings->numberOfHours = GetUserIntInput();
            while ((settings->numberOfHours < 1) || (settings->numberOfHours > 48))
                ;
        }
        else
        {
            printf("Please change forecast setting with -f first.");
        }
        break;
    case 'e':
        printf("Exiting settings menu.");
        break;
    default :
        printf("Not a valid input.");
    }
    
    UpdateSettingsFile(*settings);
}
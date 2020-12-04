#include <stdio.h>
#include <string.h>
#include "energyAppFunctions.h"

#define PLACEHOLDER 100
#define SETTINGS_FILE "settings.txt"
#define ERROR_FILE "Could not open the file %s"
#define ERROR_SCAN_RETRY "Invalid input! Try again"

typedef struct
{
    char location[PLACEHOLDER];
    int forecast;
    int numberOfHours;
    int green;
} settings;

int CheckSettings();
settings CreateSettingsStruct();
void UpdateSettingsFile(settings settings);
void UpdateSettingsStruct();

/**
 * @brief Returns 1 if the settings file exists. 0 if it does not exist.
 * 
 * @return int 
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

settings CreateSettingsStruct()
{
    settings settings;
    char buffer[10];
    char charBuffer;
    printf("Create user settings.\n"
    "Are you in DK1 or DK2?\n");
    scanf("%s", buffer);
    while(strcmp(buffer, "DK1") && strcmp(buffer, "DK2")){
        printf(ERROR_SCAN_RETRY);
        scanf("%s", buffer);
    }
    printf("%s\n", buffer);
    strcpy(settings.location, buffer);
    printf("%s\n", settings.location);
    printf("Do you wish to see a forecast? (y/n)\n");
    scanf(" %c", &charBuffer);
    printf("%c", charBuffer);
    while(charBuffer != 'y' && charBuffer != 'n'){
        printf(ERROR_SCAN_RETRY);
        scanf(" %c", &charBuffer);
    }
    settings.forecast = charBuffer == 'y' ? 1 : 0;
    settings.numberOfHours = 0;
    while(settings.forecast && (settings.numberOfHours >= 48 || settings.numberOfHours <= 0)){
        printf("How many hours do you wish to compare? (1-48)\n");
        scanf("%d", &settings.numberOfHours);
    }
    printf("Do you wish us to evaluate if the energy is green right now? (y/n)\n");
    scanf(" %c", &charBuffer);
    while(charBuffer != 'y' && charBuffer != 'n'){
        printf(ERROR_SCAN_RETRY);
        scanf(" %c", &charBuffer);
    }
    settings.green = charBuffer == 'y' ? 1 : 0;

    return settings;
}

void UpdateSettingsFile(settings settings)
{
    FILE *settingsFile = fopen(SETTINGS_FILE, "w");

    if (settingsFile == NULL)
    {
        printf(ERROR_FILE, SETTINGS_FILE);
    }
    fputs(settings.location, settingsFile);
    fprintf(settingsFile, "\n%d", settings.forecast);
    fprintf(settingsFile, "\n%d", settings.numberOfHours);
    fprintf(settingsFile, "\n%d", settings.green);

    fclose(settingsFile);
}

int main(void)
{
    settings settings;
    printf("Location: %d\n", settings.numberOfHours);
    settings = CreateSettingsStruct();
    UpdateSettingsFile(settings);

    printf("Location: %d\n", settings.numberOfHours);

    return CheckSettings();
}
#include <stdio.h>
#include <ctype.h>
#include "energyAppFunctions.h"

/**
 * @brief Validates the @param candidate if it is equal to either of the parameters
 * 
 * @param candidate the input to be tested for
 * @param option1 the first input to be tested against
 * @param option2 the second input to be tested against
 * @return int 
 */
int ValidateCharInput(char candidate, char option1, char option2){
    if((candidate == option1) || (candidate == option2)){
        return 1;
    }
    return 0;
}

/**
 * @brief this function scans for an alpha char input and calls clean.
 *  
 * @return the scanned chararacter.
 */
char GetUserCharInput(void)
{
    char choice = 'b';
    while ((scanf("-%c", &choice) != 1) || !isalpha(choice))
    {
        CleanStandardInput();
        printf("wrong!\n");
    }
    CleanStandardInput();
    return choice;
}

/**
 * @brief This function scands for an integer input and calls clean.
 * 
 * @return the scanned int.
 */
int GetUserIntInput(void)
{
    int choice = 0;
    while (scanf("-%d", &choice) != 1)
    {
        CleanStandardInput();
        printf("%d", choice);
        printf("Wrong!\n");
    }
    CleanStandardInput();

    return choice;
}

/**
 * @brief this function cleans the input buffer.
 * @return int 
 */
void CleanStandardInput()
{
    char buffer;
    while ((buffer = getchar()) != '\n' && buffer != EOF)
        ;
}

/**
 * @brief What does Command do?
 * 
 * @param settings 
 * @return char 
 */
char Command(Settings settings)
{
    printf("chose a command, write '-h' for help\n");
    char choice;
    choice = GetUserCharInput();

    switch (choice)
    {
    case 'h':
        printf("-h to open help\n -s to change settings\n -g to do graphs\n -r to run the\b -e to exit the program\n");
        return 'h';
        break;
    case 's':
        printf("lets open settings then\n");
        UpdateSettingsMenu(settings);
        return 's';
        break;
    case 'g':
        printf("not yet implemented");
        return 'g';
        break;
    case 'r':
        printf("here we go again\n");
        RunProgram(settings);
        return 'r';
        break;
    case 'e':
        printf("thanks for using\n");
        return 'e';
        break;
    default:
        printf("not a valid input\n");
        return 'z';
        break;
    }
}
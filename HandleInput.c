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
char CharInput(void)
{
    char choice = 'b';
    while ((scanf("-%c", &choice) != 1) || !isalpha(choice))
    {
        CleanStdin();
        printf("wrong!\n");
    }
    CleanStdin();
    return choice;
}

/**
 * @brief This function scands for an integer input and calls clean.
 * 
 * @return the scanned int.
 */
int IntInput(void)
{
    int choice = 0;
    while (scanf("-%d", &choice) != 1)
    {
        CleanStdin();
        printf("%d", choice);
        printf("Wrong!\n");
    }
    CleanStdin();

    return choice;
}

/**
 * @brief this function cleans the input buffer.
 * @return int 
 */
void CleanStdin()
{
    char buffer;
    while ((buffer = getchar()) != '\n' && buffer != EOF)
        ;
}
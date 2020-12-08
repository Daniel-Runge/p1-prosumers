#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>
#include "energyAppFunctions.h"

/**
 * @brief Validates the @param candidate if it is equal the @param num of options.
 * 
 * @param candidate the input to be tested for.
 * @param num the number of elements to test against.
 * @param ... all the characters to test against.
 * @return int 
 */
int ValidateCharInput(char candidate, int num, ...){
    va_list valist;
    int i;
    va_start(valist, num);

    for(i = 0; i < num; i++){
        if (candidate == va_arg(valist, char)){
            return 1;
        }
    }

    va_end(valist);
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
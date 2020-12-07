#include <stdio.h>
/**
 * @brief Validates the @param candidate if it is equal the two options.
 * 
 * @param candidate the input tested against:
 * @param option1 the first possible character.
 * @param option2 the second possible character.
 * @return int 
 */
int ValidateCharInput(char candidate, char option1, char option2)
{
    if(candidate == option1 || candidate == option2){
        return 1;
    } else {
        return 0;
    }
}

/**
 * @brief this function scans for an alpha char input and calls clean.
 * source: 
 * @return the scanned chararacter.
 */
char CharInput (void){
    char choice='b', c;
    while (((scanf("-%c%c", &choice, &c) != 2 || c != '\n') 
             && clean_stdin()) || !isalpha(choice)){
                 printf("wrong!\n");
             }

    return choice;
}

int IntInput(void){
    int choice = 0;
    while(scanf("-%d") != 1 && clean_stdin()|| !isdigit(choice)){
        printf("Wrong!\n");
    }
}

/**
 * @brief this function cleans the input buffer.
 * @return int 
 */
int clean_stdin()
{
    char buffer;
    while ((buffer = getchar()) !='\n' && buffer != EOF);
    return 1;
}
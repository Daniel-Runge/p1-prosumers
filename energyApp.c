#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "energyAppFunctions.h"

 

int main(void)
{
    char Cmd;
    
    if(1)
    {
        EnergiApp();
    }
    else
    {
        UpdateSettings();
        EnergiApp();
    }

    do{
        Cmd = Command();
    }
    while(Cmd != 'e');
    
    return 0;   
}    
    
/**
 * @brief this fuction just writes some help and is a switch that chooses which switch based on output from the input func.
 * it also returns a char that is uses by the main func to know when to exit.
 * 
 * @return char 
 */
char Command ()    
{
    printf("chose a command, write '-h' for help\n");
    char boss;
    boss = Input();

    switch (boss){
        case 'h':
            printf("-h to open help \n-s to change settings \n -g to do graphs\n -r to run the \b -e to exit the program\n");
            return 'h';
            break;
        case 's':
            printf("lets open settings then\n");
            UpdateSettings();
            return 's';
            break;
        case 'g':
            printf("not yet implemented");
            return 'g';
            break;
        case 'r':
            printf("here we go again\n");
            EnergiApp();
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

/**
 * @brief this is the primary function which is just a gathering of other functions and making of structs.
 * its where all the non structure stuff happens.
 * 
 */
void EnergiApp(void)
{
    data_total total;
    data_consumption consumption;
    /* curl_global_init(CURL_GLOBAL_ALL); */

    fileMaker();
    readFile(&total);
    green_power(&total);
    welcomeprint();
    printdata(total, consumption, green_power(&total));
    /*curl_global_cleanup();*/

}
void UpdateSettings (void){}

/**
 * @brief this function takes the input checks if its correct and then returns it.
 * @return char 
 */
char Input (void){
    char boss='b', c;
    while (((scanf("-%c%c", &boss, &c) != 2 || c != '\n') 
             && clean_stdin()) || !isalpha(boss)){
                 printf("wrong!");
             }

    return boss;
    
}
/**
 * @brief this function just checks if the stdin is clean to make sure its not printing from old input. and also cleans it.
 * @return int 
 */
int clean_stdin()
{
    while (getchar() != '\n');
    return 1;
}

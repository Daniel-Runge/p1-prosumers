#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "energyAppFunctions.h"


char Command (void);
void EnergiApp(void);
void UpdateSettings(void);
char Input (void);

int clean_stdin(); 


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
char Input (void){
    char boss='b', c;
    while (((scanf("-%c%c", &boss, &c) != 2 || c != '\n') 
             && clean_stdin()) || !isalpha(boss)){
                 printf("wrong!");
             }

    return boss;
    
}

int clean_stdin()
{
    while (getchar() != '\n');
    return 1;
}

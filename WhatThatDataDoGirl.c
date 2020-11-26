/*
* Vi læser data
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* Struct for all the numbers given */
struct APIData
{
    int CarbonIntensity;
    int Renewable;
    int FossileFree;
    int SolarCon;
    int WindCon;
    int HydroCon;
    int BiomassCon;
    int Nuclear;
    int Import;
    int Export;
};


/**
 * @brief Copypaste work so far
 * Will be adjusted so it can scan data into our struct
 * @return type is int because it's the main function right now
 */
int main(void) 
{
   FILE *fp;
   char Sentence;
   int a = 0;

   fp = fopen("cattest.JSON", "r");
   Sentence = fgetc(fp);
   printf("Procentdelen af elektriciteten der kommer fra vedvarende energi er: ");
   while (Sentence != EOF)
   {
       if(Sentence == ',')
       {
           a++;
       }
       if (a == 37 && isdigit(Sentence) == 1)
       {
           printf("%c", Sentence);
       }
       Sentence = fgetc(fp);
   }
   printf("%%");
   
   fclose(fp);
   printf("\n");
   return(0);












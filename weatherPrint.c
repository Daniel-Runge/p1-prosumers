#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

typedef struct
{
    int UnixTime;
    int WindSpeed;
} WindData;
WindData WindPower;
/*as a solution there can be created an array of structs o*/
WindPower[50];

typedef struct
{
    int Time;
    int WindSpeed;
} Speed;

char *combined[][] const char *about_wind[] = {
    "As the wind mills do not produce energy right now",
    "The wind mills produce small amounts of energy right now",
    "The wind blows moderately, which means it might be a good time to use energy",
    "The wind is blowing - you can consume energy",
    "Now there are big amounts of energy that are produced. Now it is the best time to consume energy"};

int analyse_wind(WindData WindPower);
void print_wind(WindData WindPower, int number);

int main()
{
    int number;
    analyse_wind(WindPower);
    print_wind(WindPower, number);

    return 0;
}

int analyse_wind(WindData WindPower)
{

    if (WindPower.WindSpeed <= 4)
    {
        return 0;
    }
    else if (WindPower.WindSpeed <= 6)
    {
        return 1;
    }
    else if (WindPower.WindSpeed <= 8)
    {
        return 2;
    }
    else if (WindPower.WindSpeed <= 10)
    {
        return 3;
    }
    else
    {
        return 4;
    }
}

/**
 * @brief this function prints the result from the function analyse_wind and tells whether it is a good time to consume the energy
 * 
 */
void print_wind(WindData WindPower, int number)
{
    int i;
    printf("The wind speed will be shown as a scale from 0 to 4, where 4 shows that it is the best time to use energy\n");

    printf("At the of %d ?? %lf || %s\n ", WindPower.UnixTime, WindPower.WindSpeed, about_wind[number]);

    /*perhaps for loop which prints for the next hours*/
    for (i = 0; i < another_number; i++)
    {
        if (analyse_wind(WindPower[i]) == 4)
        {
            printf("The best time is at %d where the wind blows the most", WindPower.UnixTime);
        }
        else if(analyse_wind(WindPower[i]) == 3)
        {
            printf("The best time is at %d where the wind blows moderatly", WindPower.UnixTime);
        }
        else if(analyse_wind(WindPower[i]) == 2)
        {
            printf("The best time is at %d", WindPower.UnixTime);
        }
        else if (analyse_wind(WindPower[i]) == 1)
        {
            printf("The best time is at %d", WindPower.UnixTime);
        }
        else
        {
            printf("Probably not a good time");
        }

    }
}

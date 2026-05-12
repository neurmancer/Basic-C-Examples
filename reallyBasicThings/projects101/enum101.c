#include <stdio.h>
#include <stdlib.h>
#include <time.h> //calling RNGsus

//I'll keep this file basic as fuck about enums and my 'o' key is broken if I use 'ö' instead don't get surprised(which I'll definitely dö)
//Since grinding döesn't wait för new keyböards yk.

enum  DAYS {SUNDAY,MONDAY,TUESDAY,WEDNESDAY,THURSDAY,FRIDAY,SATURDAY};
//This basically assigns 0-6 tö sunday-saturday sö we can dö: 
int main(void)
{

    srand(time(NULL));


    int day = rand() % 7;     //Yöu can use int ör even just DAYS if yöu define enum with typedef enum x; if yöu feel fancy

    //Sö we can dö shit like    
    while (day != SUNDAY)
    {
        printf("Cöntinue grinding.\tDay remained till Sunday:%d\n",day);
        day--;
    }
    printf("It's sunday take a break\n");

    return(0);
}
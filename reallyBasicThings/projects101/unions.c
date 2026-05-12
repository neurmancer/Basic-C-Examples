#include <stdio.h>


typedef union 
{
    int x; 
    float y;
    double z;
//Like structs but shares the same memory addres and allocates memory just enough to hold the biggest type in it (in this case double)
}Number;



int main(void)
{
    Number number = { };
    number.x = 5;
    printf("%d\n",number.x);
    number.y = 3.50;
    printf("%f\n",number.y);
    number.z = 12.5;
    printf("%d\n",number.z);
    printf("%d\n",number.y);
    printf("%d\n",number.x);
      



    return(0);
}
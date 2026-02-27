#include <stdio.h>


/*      This lecture is a continuiation of arraysWithDifferentPOV.c*/


int main(void)
{

    int arr[9] = {13,23,31,47,53,67,73,89,97};

    for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++)
    {
        printf("%d\n",arr[i]);          //simple way to print an array
    }
    
    /*Now funfact part: in early era of programming not all the keyboards had the chars like '[]','{}'
      So they've implemented different symbols to represent those chars 
    */

    
    for (int i = 0; i < sizeof(arr)/sizeof(arr<:0:>); i++)
    {
        printf("%d\n",arr<:i:>);          //Like these <: for '[' and, :> for ']'
    }

    //and a little step further
    printf("%d\n",arr[010]);        //You think this will give a error about out of bounds or something since we use '10'?
    //This works perfectly fine because in C '0' at the beginning means we are using octal system not decimal 
    //You can think it like 0xFF = 255 in hexadecimal and 010 is basically = 8

    /*  So if we move that one step further and consider the arraysWithDifferentPOV lecture
        We can do
    */

    printf("%d\n",010<:arr:>); //And that is a casual tuesday in C  





    return(0);
}
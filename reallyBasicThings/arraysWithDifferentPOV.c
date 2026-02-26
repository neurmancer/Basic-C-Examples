#include <stdio.h>


/*This lecture is all about showing how pointers and arrays are the same coin just different faces*/
int main(void)
{

    int arr[] = {13,53,689,0,-1};
    //well...this is an array ykr?

    int *ptr = arr; //and this is a pointer holding the address of a[0]

    for (int i = 0; i < (sizeof(arr)/sizeof(arr[0])); i++)
    {
        printf("%d\n",ptr[i]);      //basically arr[i] but with pointer
    }
    
    //Here is a little party trick

    /*
        That's where we have fun i[ptr] which is same thing not, UB not segfault 
        No compiler gonna fill for divorce
    */

    for (int i = 0; i < (sizeof(arr)/sizeof(arr[0])); i++)
    {
        printf("%d\n",i[ptr]);      
    }
    
    /*
        Reason: since arr[i] is the same as *(ptr+i) and *(i+ptr) is same shit if you graduated from middleschool 
        that means i[ptr] (or i[arr]) is same as ptr[i] and arr[i]
    */


    return(0);
}
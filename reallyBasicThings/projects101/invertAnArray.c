#include <stdio.h>


/*
    Here is a file where  show you a simple trick to walk array backwards
*/

int main(void)
{

    int arr[] = {2,3,5,7,11,13,17,19,23,29,31,37,43,53};
    
    int *arrPtr = arr+(sizeof(arr)/sizeof(arr[0]))-1; //basically the beginning of the last index (since we used -1 to go one back)
    int iter = 0;
    for (;arrPtr >= arr;arrPtr--) {
        printf("iterated: %d, address: %p\n",arr[iter],(void *)&arr[iter]);
        printf(" inverted: %d, inverted address: %p\n",*arrPtr, (void *) arrPtr);
        iter++;
    }






    return(0);
}
#include <stdio.h> //Standard IO
#include <stdlib.h> //Where the malloc and free exists

/*
        Hi kids! Do you like violence?
        Nah I ain't gonna repeat myself 
        (and that's the programming lecture of today repeat yourself as less as possible)
        anyways this gonna be about handling input allocating an int array 
        (or any array since you can allocate basically an int or int array you can allocate for anything
        in the end since all of them are just memory addresses in the end
        (yeah that's a linkin park reference and that was the song of this lecture))  
*/


int main(void)
{
 
    int *ptr = NULL;        //assing to something but not just declare even a segfault is better than UB...
                            //  I prefer harsh truth than a blanked knit with lies and UB is a blanket woven with lies
    // printf("%d\n",*ptr); and for fuck sake don't deref a null pointer or segfault will segassult your ass
    //  with a core dump harder than how she dumped me
    
    int userInput = 0; //assing shit even tho will get overwritten by scanf right after
    
    
    printf("How many number you'll enter: ");
    fflush(stdout);  //FFlush before scanf
    
    if(scanf(" %d",&userInput) != 1)
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) 
        {c++; //Sisyphus of this program...one must imagine c++ happy *wink wink*

        /*Nothing to see here just clearing input buffer*/
        }
        printf("Try again next time with actual nums yk\n.");
        return(-13);
    }
    
    int byteSize = sizeof(int)*userInput; //too reduce confusion in malloc parameters
                /*You can check if malloc fails or not with a basic if-else chain. 
                It returns NULL on fails but for the sake of simplicity and the trust I put in my Computer
                (It trusts me so I have to trust it too it's mutual)
                I am not gonna use it here and hopefully this kinda faith based error handling only be seen in my code
                and possibly in the source of TempleOS        */


    ptr = (int *) malloc(byteSize); //int * for changing the malloc's (void *) return value to int *
    int *ptr2 = ptr;            //since I'll use the ptr to assign values with array decay it'll be useless without backup 
    
    while (userInput > 0)
    {
        printf("input: ");
        fflush(stdout);     //buffer sux so we flush
        if(scanf(" %d",ptr) != 1) //The address that the pointer holding 
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {c++;/*Really...nothing to see here just clearing input buffer UnU*/ }
            printf("Try again next time with actual nums idiot\n.");
            return(-53);        //Yeah I love primes ends with 3 so what?
        }        
        ptr++; //Shifting pointer to next index
        userInput--;
    }

    for (int *p = ptr2; p < ptr2 + (byteSize/sizeof(int));p++)
    {
        printf("%d \n",*p);
    }

    free(ptr2); /*Since the ptr which we allocated decayed long ago in first loop we free the allocated address by 
                    using ptr2 still pointing the entry point
                    (Clerification: the 'decay' I used here is pure literacy as in a fallen hero 
                    (if that helps you can imagine the ptr2 as a messanger of our hero (ptr) waiting in the town knowingly 
                    that ptr won't be able to make it back safe so he must prepare the funeral for it (free))
                    and a physics pun as in radioactive decay constant(lambda) 
                    since it moved half-way(and beyond) but in the C terminology
                    array decay means when an array name decays to pointer itself such as 
                    int *ptr = arr or int *ptr = &arr[0] (mostly the first version))
                    */


    ptr = NULL;
    ptr2 = NULL; //Usually I skip the nullification (if that's a word) part since all allocation lectures end as the free happens but in production or in your own code don't forget to nullify the pointers that you've free'd

    return(0);      //I ain't giving up my boomer parens;
}
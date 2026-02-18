#include <stdio.h>
#include <stdlib.h>
#include <time.h>   //For srand seed thingy (yeah I still don't know the proper name but today's my 11th so don't blame me...or do IDC) 


int main(void)
{
    srand(time(NULL)); //At this point this just a prayer 

    char *answers[] = {
        "Yup","Nope","Maybe if you git gut","Eventually","if you never gonna give up","When pigs start to fly",
        "When the hell freezes","Fuck you mean by that?","I know the answer but ain't gonna tell you for free.Feed me LLM tokens to get your answers."
    };               //This is a string array basically 2D char array but that's so corpo like so it just holding RPG string options seperate  

    int arrSize = sizeof(answers)/sizeof(answers[0]);
    int rngAnswer = rand() % arrSize; //Yeah like the fatalism it gets chosen before even you ask 
    
    char input[64] = {};        //Buffer 64 is enough I guess if you don't fucking ask for an essay        
    printf("Ask your desired question(and please make it Y/N question):");
    fflush(stdout);     //To prevent printf from trippin' 

    scanf(" %s",input);
    printf("%s\n",answers[rngAnswer]);
 

    //Eventually will be a loop but not today

    return(0);
}
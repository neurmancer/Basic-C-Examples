/*if you've seen my other raylib.h thingies you know how I split the code and it'll be the same*/

/*      Includes        */

#include <stdio.h> //For I/O duh...
#include <stdlib.h> //For Dynamic Shit
#include <raylib.h> // For Graphs

/*
                    FULL NERDY YAP MOD (if you don't feel like it second and third paragraph is the key part rest is upon your decision)

        Have you ever heard someone saying 'Man...the hardest part of programming is writing the first line'? I say that so often and usually roll with 'fuck everything let's start with #include <stdio.h>'
        only to end up with not using it and removing after I am done with the project/file but it gives the external force to push first commit(pun intended)

        'You started to use raylib so much Neuro' yeah and I have my reasons...
            First, it's the shiny new lib that I laid my hands on so I wanna play with my new toy naturally
            Second, I am working on a project called ShittyVim (for now it's private on Github) and termios needs high attention and manual labor with it's raw mode so I cope with some abstraction raylib provides
            Third, There is a basic 'Baby's First Linux Kernel Driver' file on the way I am letting it marinete (or how tf u spell it) for a bit for better demonstration and tutorial as I expend my knowledge on it...
       
        Sup? New day new thingy i guess...so What we're building today? A Screensaver on the surface using my beloved ones. Prime numbers ofc here is the tea
        
        1-Open a borderless window
        2-Calculate primes up to UINT_MAX (side-track here 4,294,967,295 is UINT_MAX's value and last loop will check till approx. ~68k iteration so that's...gonna be harsh(I made the sqrt mentally so it can be janky)) on the fly with optimization concerns
        3-And pick a random vector on the screen (x,y) on the screen and paint the said pixel for each prime..
            Subideas for painting
                1- A monochrome screen paint for satisfaction with only one color and watch screen change skin
                2- Random selection of color from a predetermined array (that feels tempting since maybe it'll be mona lisa on the 13th run? yk...the infinite time/monkey and hamlet type shit)
                3- Changing values over time for each RGB hex so you can see guess 'warmth' of primes on the screen by just looking
                4- Or for n we can switch colors where n is the 10^n so primes upto 10 would be a color and then (10,100)would another etc.. (basically log10 and every +1 will be new color till the next +1...yeah I explain shit harder than it should be...) 
 
        And I am changing my doctrine(said the 3 weeks old coder as if he's  Kant publishing the Critique of Pure Reason and explaining a paradigm shift) in this file usually I start with a printf() or InitWindow to stimulate myself with a dopamine hit but this time we're building toolkit first so here are what we need
       
            1- A dynamic array (that's why stlib's here)
                1- A base array with let's say size of 256 elements and increase it accordingly as we go
                2- A function to wrap realloc around so we can abstarct the error handling and shit.
                3- And that's all I guess
            2- A prime founder that won't take eternity to reach UINT_MAX but here is the twist I'll implement something myself lol...no handholding or algorithm lectures I am a rouge-dev(yeah Red in french and misspelled Rogue both suits me) and the 'no hand holding' rule means that Imma be Terry Davis'ing my way through this file too lol(and yeah I use 'Terry Davis' as verb) 
            3- Two arrays for filling with resolution values (one for Width one for Height...yeah I can use a Vector2 or typedef a struct myself (I used typedef as a verb lol) but we'll see as we roll)
            4- A PRNG thing for selecting an element from the said arrays for x,y coordinates and then a function to delete the point from the array so we don't override a painted pixel
            and since I don't know how to ditch an element from an formal array of C I'll probably use two seperate exactly same linked list struct...
            probably an overkill but that what occured in mind that I can handle first...
            
            since we'll pop (or remove) elements randomly (pseudorandomly) probably this will take O(n)(Bachmann–Landau notation but
            I guess in coding we only care about worst case which is O() form instead of omega or anything else...idk) but array is sorted (as I said 1 to width/height)
            so we can use a binary search maybe(tho I don't know yet I just have ideas resemmbling the definition)
           
            Improvment Idea (yeah even before starting to type anything for this one yet)
                1- Ditch the GUI and make it CLI with using 24bit true colors and █ (if that's recolorable i need to try first lol)

            I am good at yapping we got literally nothing yet vim shows 45 rows already and I don't delete those since in a world that every program gets sterilzied people often forget who codes it...

            We humans do...And that comes with its struggles and the banter within files what makes them precious imo like have you read man page of ffplay? I read for 3 hours for some flag hunt for ShittyJukeBox project due to buffer latency of ffplay and saw people'd written things like '360p shitty buffer' '720p cool buffering' etc. that's how programming was or the original source code of doom has cusses in it because WE ARE HUMAN...I mean that's why I've chosen C it is messy, it resembles humanity there is no 'spacing' like python nor abstraction behind abstraction.. for example I can write 010<:arr:> and compiler just accepts (which means arr[8] btw more on that later)
         

*/

/*      #Defines#       */

/*     Declarations      */
struct n{
    int x; //I'll use the same struct for both for height and width twice so I selected an neutral var name
    struct n *next; //Yeah I am improvising DSA too lmfao
};

typedef struct n node; 

node *sortedAdd(node *root,int value); //Both returns (node *) in case of a new root assignment (even tho add function wouldn't use it as much as delete)
node *delete(node *root, int value);
int fillLinkedList(node *root,int targetIters); //Just to keep main as minimal as possible this is probably gonna be just a loop


int main(void)
{

    /*
            Lol debug time even before typing any shit

    ==224880== Conditional jump or move depends on uninitialised value(s)
    ==224880==    at 0x40011DC: main (in /home/neuromancer/realHome/C/Projects/Basic-C-Examples/reallyBasicThings/projects101/a.out)
    ==224880==  Uninitialised value was created by a heap allocation
    ==224880==    at 0x484F8A8: malloc (vg_replace_malloc.c:446)
    ==224880==    by 0x400142C: fillLinkedList (in /home/neuromancer/realHome/C/Projects/Basic-C-Examples/reallyBasicThings/projects101/a.out)
    ==224880==    by 0x4001198: main (in /home/neuromancer/realHome/C/Projects/Basic-C-Examples/reallyBasicThings/projects101/a.out)
    ==224880== 
    --224880-- REDIR: 0x492c080 (libc.so.6:free) redirected to 0x4852980 (free)
    ==224880== Conditional jump or move depends on uninitialised value(s)
    ==224880==    at 0x4001357: delete (in /home/neuromancer/realHome/C/Projects/Basic-C-Examples/reallyBasicThings/projects101/a.out)
    ==224880==    by 0x40011FB: main (in /home/neuromancer/realHome/C/Projects/Basic-C-Examples/reallyBasicThings/projects101/a.out)
    ==224880==  Uninitialised value was created by a heap allocation
    ==224880==    at 0x484F8A8: malloc (vg_replace_malloc.c:446)
    ==224880==    by 0x400142C: fillLinkedList (in /home/neuromancer/realHome/C/Projects/Basic-C-Examples/reallyBasicThings/projects101/a.out)
    ==224880==    by 0x4001198: main (in /home/neuromancer/realHome/C/Projects/Basic-C-Examples/reallyBasicThings/projects101/a.out)
    ==224880== 
    ==224880== Conditional jump or move depends on uninitialised value(s)
    ==224880==    at 0x4001205: main (in /home/neuromancer/realHome/C/Projects/Basic-C-Examples/reallyBasicThings/projects101/a.out)
    ==224880==  Uninitialised value was created by a heap allocation
    ==224880==    at 0x484F8A8: malloc (vg_replace_malloc.c:446)
    ==224880==    by 0x400142C: fillLinkedList (in /home/neuromancer/realHome/C/Projects/Basic-C-Examples/reallyBasicThings/projects101/a.out)
    ==224880==    by 0x4001198: main (in /home/neuromancer/realHome/C/Projects/Basic-C-Examples/reallyBasicThings/projects101/a.out)
    ==224880== 
    ==224880== 
    ==224880== HEAP SUMMARY:
    ==224880==     in use at exit: 0 bytes in 0 blocks
    ==224880==   total heap usage: 7 allocs, 7 frees, 1,120 bytes allocated
    ==224880== 
    ==224880== All heap blocks were freed -- no leaks are possible

    
    
    */
    node *root = (node *)malloc(sizeof(node));
    if (root == NULL) { return(-1); }

    node *iter = root;
    //IDK how long this file gonna be so I don't wanna risk touching root directly (for the DSA illiterates like me: if you loose a node the linked list from that point on becomes inaccessible)
    int check = fillLinkedList(iter,5);
    if (check) {
        return(1);
    }
    while(iter->next != NULL) {
        printf("%d\n",iter->x);
        iter = iter->next;
    } //Nah it works nice

    iter = root; //Reassign the iter to where it belongs
    while (iter != NULL) {
        iter = delete(iter, iter->x);
    }
    


    root = NULL; //Yeah...even my boilerplates include memory hygeine first lol
    iter = NULL;

    return(0);
}

node *sortedAdd(node *root,int value) //I'll probably WILL NOT use since I'll only fill the list with 1-WIDTH and 1-HEIGHT and iterating the linked list over and over will inefficent but I am coding anyawys 
{
    if (root == NULL) { 
        //This block is basically an edge-case...if the function gets called for the first element in the linked list
        root = (node *) (malloc(sizeof(node)));
        if (root == NULL) { return(NULL); }
        
        root->next = NULL;
        root->x = value;

        return(root);
    }

    if (root->x > value) { //Second edge case 
        node *temp = (node *)malloc(sizeof(node));
        if (temp == NULL) {return(NULL);}
        temp->x = value;
        temp->next = root;
        
        return(temp);
    }

    node *iter = root;
    while (iter->next != NULL && iter->next->x < value) 
    {
        iter = iter->next; //That is the part where my optimization concerns begin... putting this in a loop from 1-x will cause something like O(n^2) right?
    }

    node *temp = (node *)malloc(sizeof(node));
    
    if (temp == NULL) {return(NULL);}
    
    temp->x = value;
    
    temp->next = iter->next; //putting the node in between
    iter->next = temp;
    
    return(root);
}

node *delete(node *root, int value)
{
    node *temp = NULL;
    node *iter = root;
    
    if (root->x == value) { 
        temp = root;
        root = root->next;
        free(temp);
        return(root);
    }

    while (iter->next != NULL && iter->next->x != value) {
        //pretty self-explanatory but me being me: while the next node after iter is not null and not the value we seek, move on
        iter = iter->next; 
    }

    if (iter->next == NULL) {
        return(root);
    }
    temp = iter->next;
    iter->next =iter->next->next; 
    free(temp);

    return(root); 
}

int fillLinkedList(node *root, int targetIters)
{
    if (root == NULL){ return(-53); }

    node *iter = root;

    for (int i = 0; i < targetIters; i++)
    {
        iter->x = i;

        if (i == targetIters - 1)
        {
            iter->next = NULL;
        }
        else
        {
            iter->next = malloc(sizeof(node));
            if (iter->next == NULL){ return(-13); }
            iter = iter->next;
        }
    }

    return(0);
}
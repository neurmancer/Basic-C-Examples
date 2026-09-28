/*
    'Sup? this file is literally a template for a text editor since I need a CLI client for TODO-SERVER
    and future literally has a vim clone so...
    
    ...and I've broken my pinky now my whole left forearm in cast...
    Coding like that is fucking hard!!

*/


#include <termios.h>
#include <unistd.h>


void enable_raw();



int main(void)
{

    enable_raw();   //telling 'IT'S MINE NOW' to terminal




    return(0);
}


void enable_raw()
{
    struct termios raww = { 0 };

    tcgetattr(STDIN_FILENO, &raww);

    raww.c_lflag &= ~(ECHO);
    //yup comments will come in the future when I have two fucking arms
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raww);



}
#include <stdio.h>


/*
    Sup? lol I start to use 'sup' so much as I code...today's fuckery is writing our own sqrt functin (at least somethig close to that) that I can use instead of linking math.h 
    since using it just for sqrt() is so fucking pathetic...I usually skip the mathemtical explanation part since I presume you know if you check something like that but for that I'll explain

    We'll use derivaties(which gives us the slope of any function at any point) and to recap I'll just give you the formula d/dx of sqrt(x) equals 1/2*sqrt(x) I won't prove it here fuck no...
    
    simply we'll find closest perfect square number below the given sqrt(x) then plug it into the f'(x) (which is 1/(2*sqrt(x)) and get our slope (m) value then rest is just math 
    example: 
    let's say we're looking for sqrt(12) 
    1- find closest perfect sqrt which is 9 (3^2) 
    2- then plug it to the funciton where function is the f(x) = sqrt(x) to get our y coordinate so we have (x,y) which is (9,3) 
    3- Find slope using derivatives f'(x) = 1/(2*sqrt(x)) and plug our perfect square there so we'll get 1/(2*3) this is our slope 1/6
    4- write down the point-slope equation y-3 = 1/(2*3)* (x-9) then blug the x value(12) into there which will result in (1/6)*(12-9) = 3/6 
    5-simplify it, y-3 = 1/2
    6- Add +3 to each side and you'll get y = 3,5 and real answer is = ~3.46410161514
    
    And I guess this is the simple first degree Taylor series centered at the nearest integer solution
    hence I just want to try to implement this nothing crazy and I'll probably fuck up lol

*/


float sqrty(unsigned int val); //To avoid conflict with math.h


int main(void)
{

    printf("%3.5f",sqrty(689));



    return(0);
}


float sqrty(unsigned int val)
{
    if(val == 0){ return(0.0f); } //I can't work with divide by zero lol
    float result = 0;
    int i = 0;
    
    for(;i*i <= val && (i+1)*(i+1) <= val;i++){ }
    
    float z = i;
    float divide = (float)(val-(z*z)) /(float)(2*z);
    result = z+divide;

    return(result);
}
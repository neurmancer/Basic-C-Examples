/*

    'Sup? 
    Man...I'm exhasuted (this is an after shift coding session) so we'll do something silly while most of my brain fighting to get 
    the custom malloc implementation right...

    So today's low-level fuckery is writing our own printf for a few reasons:
        1-First it's objectively cool
        2-I wanted to fuck with variadic arguments
        3-I found a compiler flag and wanna test it but I couldn't put that in a separate file because it would be literally 2 lines of code

        So...here is how we roll, something old, something new method
*/


#include <unistd.h> //The low-level gremlin entry-point 
#include <stdarg.h>



void print_it(const char *format, ...); //Somehow ... being a acceptable value is messing with me
void put_char(char c);
void put_str(char *str);
void put_int(int num);
void putf(float n);


int main(void)
{

    int x = 13;
    float y = 13.53;
    char *string = "It works!";
    char c = 'A';

    print_it("Let's test the whole zoo\nint: %d\nfloat: %f\nchar: %c\nString: %s",x,y,c,string);

    /*
        Now the second part I wanna look at...
        before this part you may use it without any flags but if you wanna uncomment this you need to use 
        clang print_it.c -o your_output -fwritable-strings 
        string[0] = 'i';
        Normally char * are stored in .rodata (read only) but this clang flag allows you to chage that and yeah that was the 
        second thing that I wanted to try out
    */
    
    //as expected float has a rounding error (.529999) it was an expected outcome  
    return(0);
}  


void print_it(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    while (*format) {
        if (*format == '%') {
            format++;
            if (!*format) {
                break;
            }
            switch (*format) {
                case 'c':
                    char c = va_arg(ap, int);
                    put_char(c);
                    break;
                case 's':
                    char *str = va_arg(ap, char *);
                    put_str(str);
                    break;
                case 'd':
                    int n = va_arg(ap, int);
                    put_int(n);
                    break;
                case 'f':
                    float f = va_arg(ap, double);   //va_args expects double to pass floats don't know why...
                    putf(f);  //Put float
                    break;
                case '%':
                    put_char('%');
                    break;    
                default:
                    put_char('%');
                    put_char(*format);  //putc is taken and I don't have energy to overthink the names
                    break;
            }
        }
        else {
            put_char(*format);
        }
        format++;
    }
    va_end(ap);     //Yeah...whole pritf basically a fucking finite state machine 
}


void put_char(char c)
{
    write(1, &c, sizeof(c));
}


void put_str(char *str)
{
    while (*str) {
        // will stop when str hits '\0' 
        put_char(*str);
        str++;
    }
}

void put_int(int num)
{
    long n = num;   //To avoid overflow indeciveness

    if (n < 0) {
        put_char('-');
        n = (~n)+1;
    }

    if (n >= 10) {
        put_int(n/10); //Recursive handling thing
    }
    put_char((n % 10) + '0');    //Ascii zero as base
}


void putf(float n)
{
    int precision = 6;  //Lol like DnD session
    if (n < 0) {
        put_char('-');
        n*=-1;
    }
    int whole = (int) n; //SSE CVTTSS2SI to get the whole part;
    
    float remains = n - whole;

    put_int(whole);
    put_char('.');
    for (size_t i = 0; i < precision; i++) {
        remains *=10;
        put_int((int )remains);
        remains -= (int) remains;
    }
}
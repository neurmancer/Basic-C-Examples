#ifndef INT_MAX 
    #define INT_MAX (~0u>>1)//For INT_MAX because I ain't remembering how much is 2^31-1 or shit
#endif 
int fibonacci(int n);           //Fibonacci sequenec calcualtor and yeah I feel more comfortable declaring at the top and giving functioniality (or how tf you spell that) at down
int fibonacciCursed(int n);      //And fucked up way using 'recursion' 

int main(void)
{
        //Go try getting input from user and shit

    return(0);
}


int fibonacci(int n) {
    if (n < 0){return(13);}
    if (n == 0){return(0);}
    if (n == 1){return(1);}

    int first = 0, second = 1;
    for (int i = 2; i <= n; i++) {
        if (second > INT_MAX - first) {return (~(~0u>>1)+1);}  // will overflow on next add (and yeah I didn'T use INT_MIN on purpose)
        int sum = first + second;
        first = second;
        second = sum;
    }
    return(second);
}

int fibonacciCursed(int n)          //Seems better right? but fuck no this shit is a CPU fucker for each recursion it calculates old values twice like for f(3) = f(2) + f(1) and f(2) calculates f(1)+f(0) again and again
{
    if (n == 0){return(0);}
    else if (n == 1){return(1);}
    else{
        return(fibonacciCursed(n-1)+fibonacciCursed(n-2));
    }
}
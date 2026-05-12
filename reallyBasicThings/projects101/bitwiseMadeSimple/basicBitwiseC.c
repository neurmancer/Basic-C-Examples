#include <stdio.h>



int main(void)
{


	unsigned int x,y,z;
	x = 6; //00000110
	y = 1; //00000001    
	z = x & y; //AND operator will give 0000000 = 0
	z = x | y; //OR operator will give 00000111 = 7
	y << 2; //shitf bits 2 places to the left and assing 0 to the old places. Basically multiply by 4
	z >> 1; // divide in halves by moving bits to left and the last bit will vanish puf. so 7 will be 00000011 which is 3(7/2 = 3.5)but the fraction is gone
	z = ~z; //Converts each 1 bit to 0 and vice versa 

	return(0);
}

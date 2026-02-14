#include <stdio.h>
#include <unistd.h>
//This script is to remind myself how to 2D string arrays work


int main(void)
{

	char lyrics[30][120] = {"How can you see into my eyes like open doors?","Leading you down into my core","Where I've become so numb",
		"Without a soul","My spirit's sleeping somewhere cold","Until you find it there and lead it back home",
		"Wake me up inside (save me)","Call my name and save me from the dark (wake me up)","Bid my blood to run (I can't wake up)","Before I come undone (save me)",
		"Save me from the nothing I've become","Now that I know what I'm without","You can't just leave me","Breathe into me and make me real","Bring (bring) me (me) to life"};


	for (int i = 0; i < 15 ; i++)
	{
		printf("%s\n",lyrics[i]);
		usleep(222222);
	}

	return(0);
}

#include <unistd.h>
#include <stdio.h>
#include <time.h>

#define NO_CURSOR "\033[?25l"

int main(void)
{
	setvbuf(stdout, NULL, _IONBF, 0);

	const char *spin_chars = "|/-\\";
	const char *dots = "...";
	time_t start = time(NULL);
	int spinner = 0;
	printf(NO_CURSOR);
	while (difftime(time(NULL),start < 10.0)) {
		
		printf("\r%c loading shit",spin_chars[spinner % 4]); //I guess with that I overcame a little of my hard coding habbits
		usleep(180000);
		spinner++;
	}

	printf("\033[?25h\n");


	return(0);
}

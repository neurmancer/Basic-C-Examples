#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define SECOND 1000000000

//Just experimenting with termios don't mind me 

static struct termios oldTermios, newTermios;

void configTerm(void)
{
  tcgetattr(STDIN_FILENO, &oldTermios);
  newTermios = oldTermios;

  newTermios.c_lflag &= ~(ICANON | ECHO);
  newTermios.c_cc[VMIN] = 0;
  newTermios.c_cc[VTIME] = 0;

  tcsetattr(STDIN_FILENO, TCSANOW, &newTermios);
}

void fixTerm(void)
{

  printf("\033[25h");
  printf("\033[H\033[J");

  tcsetattr(STDIN_FILENO, TCSANOW, &oldTermios);
}

int readKey(char *buf, int k)
{


  if(buf[k] == '\033' && buf[k+1] == '[')
  {
    switch (buf[k+2]) {
      case 'A':
        return(1);
      case 'B':
        return(2);
      case 'C':
        return(3);
      case 'D':
        return(4);
    }
  }
  return(0);
}

int readInput(void)
{

  char buf[4096];
  int n = read(STDIN_FILENO, buf, sizeof(buf));
  int keyStroke = 0;

  for (int k = 0; k <= n-3; k+=3) {

    int key = readKey(buf, k);
    
    if (!key) { continue; }
    keyStroke = key;
  }

  return(keyStroke);
}


void printArrows(int key)
{
  switch (key) {

    case 1:
      printf("Up\n");
      break;
    case 2:
      printf("Down\n");
      break;
    case 3:
      printf("Right\n");
      break;
    case 4:
      printf("Left\n");
      break;
  }
}

int main(void)
{

  configTerm();
  
  struct timespec req = { 0 };
  struct timespec rem = { 0 };
  int key = 0;

  while (key != -1) {
    key = readInput();
    printArrows(key);

    req.tv_nsec = 0.1 * SECOND;
    nanosleep(&req, &rem);
  }

  fixTerm();

  return(0);
}

#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    char *name;
    char *surname;
    float GPA;
    int ID;
}Student; //Yeah same as last one


int main(void)
{

    Student student = {"Jane","Doe",4.20,1005};
    Student *studentPtr = &student;

    printf("Name:%s\n",(*studentPtr).name);
    printf("Surname:%s\n",studentPtr->surname); //or you can do that

    return(0);
}
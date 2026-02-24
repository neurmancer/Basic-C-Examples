#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    char *name;
    char *surname;
    float GPA;
    int ID;
}Student;

int main(void)
{
    Student *student = NULL;

    student = (Student*) malloc(sizeof(Student));
    
    strcpy(student->name,"John");
    strcpy(student->surname,"Doe");
    student->ID = 1353689;
    student->GPA = 4.54;
    //Like that not much different than yk allocating any other memory 


    free(student);



    return(0);
}
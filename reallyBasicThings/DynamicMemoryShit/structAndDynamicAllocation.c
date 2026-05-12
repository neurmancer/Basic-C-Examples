#include <stdlib.h>
#include <string.h>

typedef struct 
{
    char name[30];
    char surname[30];
    float GPA;
    int ID;
}Student;

int main(void)
{
    Student *student = NULL;

    student = (Student*) malloc(sizeof(Student));
   
    
    strcpy(student->name,"Thea"); //Bro I swear I don't have ancient Greek Goddess Fetishes
    strcpy(student->surname,"Aurora");
    student->ID = 1368953;
    student->GPA = 4.26;
    //Like that not much different than yk allocating any other memory 


    free(student);



    return(0);
}
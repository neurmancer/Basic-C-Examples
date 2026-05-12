#include <stdio.h>
#include <stdlib.h>


typedef struct 
{
    char *name;
    char *surname;
    int ID;
    float GPA;
}Student;


int main(void)
{

    Student students[] = {{"Thea","Smith",1001,4.05},"Atlas","Alvarez",1002,3.65};

    printf("Name:%s\tSurname:%s\nID:%d\tGPA:%2.2f\n",students[0].name,students[0].surname,students[0].ID,students[0].GPA);

    /*Basically arrays that you provide needed struct data in not so much different than the usual int arrays*/
    

    return(0);
}
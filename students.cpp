#include "globals.h"

void view_details(){
    cout<<"Student Details:\n";
    cout<<"Name: "<<students[student_login()].name<<endl;
    cout<<"Age: "<<students[student_login()].age<<endl;
    cout<<"Program: "<<students[student_login()].program<<endl;
    cout<<"Student ID: "<<students[student_login()].studentID<<endl;
}

void view_grades(){
    cout<<"Student Grades:\n";
    for(int i = 0; i < 6; i++){
        cout<<"Subject "<<i+1<<": "<<students[student_login()].grades[i]<<endl;
    }    
}
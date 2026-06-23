#include "globals.h"

void view_details(int index){
    system("cls");
    cout<<"==================== Student Details ====================\n";
    cout<<"Name: "<<students[index].name<<endl;
    cout<<"Age: "<<students[index].age<<endl;
    cout<<"Program: "<<students[index].program<<endl;
    cout<<"Student ID: "<<students[index].studentID<<endl;
    system("pause");
}

void view_grades(int index){
    system("cls");
    cout<<"==================== Student Grades ====================\n";
    string subjects[6] = {"MA110", "LA111", "PH110", "CS120", "CS130", "CS150"};
    cout<<"Student Grades:\n";
    for(int i = 0; i < 6; i++){
        cout<<subjects[i]<<": "<<students[index].grades[i]<<endl;
    }
    system("pause");
}
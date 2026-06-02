#include <iostream>
#include <limits>
#include "students.h"
#include <string>
using namespace std;

Student students[100];
int student_count = 0;

void add_students(){
    cout<<"Enter Full Name: ";
    getline(cin, students[student_count].name);
    cout<<"Enter Age: ";
    cin>>students[student_count].age;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout<<"Enter Program: ";
    getline(cin, students[student_count].program);
    student_count++;
    cout<<"Student added successfully!\n";
}

void view_all_students(){
    for(int i = 0; i < student_count; i++){
        cout<<"\nName: "<<students[i].name<<endl;
        cout<<"Age: "<<students[i].age<<endl;
        cout<<"Program: "<<students[i].program<<endl;
        cout<<"_____________________________________\n\n";
    }
}

void search_students(){
    cout<<"Enter name to search: ";
    string search_name;
    getline(cin, search_name);
    bool found = false;
    for(int i = 0; i < student_count; i++){
        if(students[i].name == search_name){
            cout<<"\nName: "<<students[i].name<<endl;
            cout<<"Age: "<<students[i].age<<endl;
            cout<<"Program: "<<students[i].program<<endl;
            cout<<"_____________________________________\n\n";
            found = true;
        }
    }
    if(!found){
        cout<<"Student not found!\n";
    }
}
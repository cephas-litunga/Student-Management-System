#include "globals.h"

void view_details(int index){
    system("cls");
    cout<<"==================== Student Details ====================\n";
    cout<<"Name: "<<students[index].name<<endl;
    cout<<"Age: "<<students[index].age<<endl;
    cout<<"Program: "<<students[index].program<<endl;
    cout<<"Student ID: "<<students[index].studentID<<endl;
    cout<<"Email: "<<students[index].email<<endl;
    cout<<"Phone Number: "<<students[index].phone_number<<endl;
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

void change_password(int index){
    system("cls");
    string new_password, current_password;
    cout<<"==================== Change Password ====================\n";
    cout<<"Enter current password: ";
    cin>>current_password;

    while(current_password != students[index].password){
        cout<<"Incorrect current password!\n";
        cout<<"Enter current password: ";
        cin>>current_password;
    }

    cout<<"Enter new password: ";
    cin>>new_password;
    students[index].password = new_password;
    cout<<"Password changed successfully!\n";
    system("pause");
}
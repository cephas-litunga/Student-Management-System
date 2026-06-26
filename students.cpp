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

void update_info(int index){
    system("cls");
    int option;
    cout<<"==================== Update Student Info ====================\n";
    cout<<"1. Update Phone number\n";
    cout<<"2. Update Email\n";
    cout<<"3. Change password\n";
    cout<<"Enter option: ";
    cin>>option;
    
    if(option == 1){
        cout<<"Enter new phone number: ";
        cin>>students[index].phone_number;
        cout<<"Phone number updated successfully!\n";
    } else if(option == 2){
        cout<<"Enter new email: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, students[index].email);
        cout<<"Email updated successfully!\n";
    } else if(option == 3){
        change_password(index);
    } else {
        cout<<"Invalid option! Please try again.\n";
    }
}
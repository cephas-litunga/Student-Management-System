#include "globals.h"

void view_lecturer_details(int lecturer_index){
    system("cls");
    cout<<"==================== Lecturer Details ====================\n";
    cout<<"Name: "<<lecturer[lecturer_index].name<<endl;
    cout<<"Email: "<<lecturer[lecturer_index].email<<endl;
    cout<<"Phone Number: "<<lecturer[lecturer_index].phone_number<<endl;
    cout<<"Lecturer ID: "<<lecturer[lecturer_index].lecturerID<<endl;
    system("pause");
}

void update_lecturer_info(int lecturer_index){
    system("cls");
    cout<<"==================== Update Lecturer Info ====================\n";
    cout<<"Enter Email: ";
    getline(cin, lecturer[lecturer_index].email);
    cout<<"Enter Phone Number: ";
    cin>>lecturer[lecturer_index].phone_number;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout<<"Lecturer Details updated successfully!\n";
    system("pause");
}

void change_lecturer_password(int lecturer_index){
    system("cls");
    cout<<"==================== Change Lecturer Password ====================\n";
    string new_password;
    cout<<"Enter new password: ";
    getline(cin, new_password);
    lecturer[lecturer_index].password = new_password;
    cout<<"Password changed successfully!\n";
    system("pause");
}
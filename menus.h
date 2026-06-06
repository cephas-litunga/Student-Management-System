#ifndef MENUS_H
#define MENUS_H

#include <iostream>
#include <limits>
using namespace std;

static inline int main_menu(){
    int mm_option;
    cout<<"\n============ Student Management System =================\n";
    cout<<"1. Add Student\n";
    cout<<"2. Search Student\n";
    cout<<"3. View all students\n";
    cout<<"4. Edit Student Grades\n";
    cout<<"5. Edit Student Details\n";
    cout<<"6. View Student Grades\n";
    cout<<"7. Delete Student\n";
    cout<<"8. Exit\n";
    cout<<"Enter option: ";
    cin>>mm_option;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return mm_option;
}



#endif
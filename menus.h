#ifndef MENUS_H
#define MENUS_H

#include <iostream>
using namespace std;

static inline int main_menu(){
    int mm_option;
    cout<<"============ Student Management System =================\n";
    cout<<"1. Add Student\n";
    cout<<"2. Search Student\n";
    cout<<"3. View all students\n";
    cout<<"4. View Student Grades\n";
    cout<<"5. Edit Student Details\n";
    cout<<"6. Edit Grades\n";
    cout<<"7. Exit\n";
    cout<<"Enter option: ";
    cin>>mm_option;
    return mm_option;
}



#endif
#ifndef MENUS_H
#define MENUS_H

#include <iostream>
#include <limits>
using namespace std;

static inline int admin_control_menu(){
    int acm_option;
    system("cls");
    cout<<"============ Welcome Admin =================\n";
    cout<<"1. Register Student\n";
    cout<<"2. Search Student\n";
    cout<<"3. View all students\n";
    cout<<"4. Edit Student Grades\n";
    cout<<"5. Edit Student Details\n";
    cout<<"6. View Student Grades\n";
    cout<<"7. Delete Student\n";
    cout<<"8. Logout\n";
    cout<<"Enter option: ";
    cin>>acm_option;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return acm_option;
}

static inline int home_menu(){
    int hm_option;
    system("cls");
    cout<<"============ Student Management System Login =================\n";
    cout<<"1. Login\n";
    cout<<"2. Exit\n";
    cout<<"Enter option: ";
    cin>>hm_option;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return hm_option;
}

static inline int login_menu(){
    system("cls");
    int lm_option;
    cout<<"============ Student Management System Login =================\n";
    cout<<"1. Admin Login\n";
    cout<<"2. Student Login\n";
    cout<<"3. Back\n";
    cout<<"Enter option: ";
    cin>>lm_option;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return lm_option;
}

static inline int admin_menu(){
    int am_option;
    system("cls");
    cout<<"============ Admin Menu =================\n";
    cout<<"1. Add Student\n";
    cout<<"2. Search Student\n";
    cout<<"3. View all students\n";
    cout<<"4. Edit Student Grades\n";
    cout<<"5. Edit Student Details\n";
    cout<<"6. View Student Grades\n";
    cout<<"7. Delete Student\n";
    cout<<"8. Logout\n";
    cout<<"Enter option: ";
    cin>>am_option;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return am_option;
}

static inline int student_menu(){
    int sm_option;
    system("cls");
    cout<<"============ Student Portal Menu =================\n";
    cout<<"1. View Grades\n";
    cout<<"2. View Details\n";
    cout<<"3. Update info\n";
    cout<<"4. Logout\n";
    cout<<"Enter option: ";
    cin>>sm_option;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return sm_option;
}



#endif
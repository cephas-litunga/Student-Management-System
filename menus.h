#ifndef MENUS_H
#define MENUS_H

#include <iostream>
#include <limits>
using namespace std;

static inline int validateInput(int min, int max) {
    int input;
    while (true) {
        cin >> input;
        if (cin.fail() || input < min || input > max) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between " << min << " and " << max << ": ";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return input;
        }
    }
}

static inline int admin_menu(){
    int acm_option;
    system("cls");
    cout<<"============ Welcome Admin =================\n";
    cout<<"1. Student Management\n";
    cout<<"2. Lecturer Management\n";
    cout<<"3. Course Management\n";
    cout<<"4. Logout\n";
    cout<<"Enter option: ";
    acm_option = validateInput(1,4);
    return acm_option;
}

static inline int home_menu(){
    int hm_option;
    system("cls");
    cout<<"============ Student Management System Login =================\n";
    cout<<"1. Login\n";
    cout<<"2. Exit\n";
    cout<<"Enter option: ";
    hm_option = validateInput(1,2);
    return hm_option;
}

static inline int login_menu(){
    system("cls");
    int lm_option;
    cout<<"============ Student Management System Login =================\n";
    cout<<"1. Admin Login\n";
    cout<<"2. Student Login\n";
    cout<<"3. Lecturer Login\n";
    cout<<"4. Back\n";
    cout<<"Enter option: ";
    lm_option = validateInput(1,4);
    return lm_option;
}

static inline int lecturer_menu(){
    int lm_option;
    system("cls");
    cout<<"============ Lecturer Portal Menu =================\n";
    cout<<"1. View Details\n";
    cout<<"2. Update info\n";
    cout<<"3. Logout\n";
    cout<<"Enter option: ";
    lm_option = validateInput(1,3);
    return lm_option;
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
    sm_option = validateInput(1,4);
    return sm_option;
}

static inline int course_management_menu(){
    int cmm_option;
    system("cls");
    cout<<"============ Course Management Menu =================\n";
    cout<<"1. Add Course\n";
    cout<<"2. View all Courses\n";
    cout<<"3. Delete Course\n";
    cout<<"4. Search Course\n";
    cout<<"5. Edit Course\n";
    cout<<"6. Back\n";
    cout<<"Enter option: ";
    cmm_option = validateInput(1,6);
    return cmm_option;
}

static inline int student_management_menu(){
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
    cout<<"8. Back\n";
    cout<<"Enter option: ";
    am_option = validateInput(1,8);
    return am_option;
}

static inline int lecturer_management_menu(){
    int lm_option;
    system("cls");
    cout<<"============ Lecturer Management Menu =================\n";
    cout<<"1. Add Lecturer\n";
    cout<<"2. Search Lecturer\n";
    cout<<"3. View all Lecturers\n";
    cout<<"4. Edit Lecturer Details\n";
    cout<<"5. Delete Lecturer\n";
    cout<<"6. Back\n";
    cout<<"Enter option: ";
    lm_option = validateInput(1,6);
    return lm_option;
}

#endif
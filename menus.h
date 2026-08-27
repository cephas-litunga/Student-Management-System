#ifndef MENUS_H
#define MENUS_H

#include "validation.h"
#include <iostream>
// #include "globals.h"
#include <limits>
using namespace std;


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
    cout<<"3. Change Password\n";
    cout<<"4. View Assigned Courses\n";
    cout<<"5. Manage Results\n";
    cout<<"6. Logout\n";
    cout<<"Enter option: ";
    lm_option = validateInput(1,6);
    return lm_option;
}

static inline int student_menu(){
    int sm_option;
    system("cls");
    cout<<"============ Student Portal Menu =================\n";
    // cout<<"1. View Grades\n";
    cout<<"1. View Details\n";
    cout<<"2. View CA results\n";
    cout<<"3. View Final results\n";
    cout<<"4. Update info\n";
    cout<<"5. Change Password\n";
    cout<<"6. Course Registration\n";
    cout<<"7. Logout\n";
    cout<<"Enter option: ";
    sm_option = validateInput(1,7);
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
    // cout<<"4. Edit Student Grades\n";
    cout<<"4. Edit Student Details\n";
    // cout<<"6. View Student Grades\n";
    cout<<"5. Delete Student\n";
    cout<<"6. Back\n";
    cout<<"Enter option: ";
    am_option = validateInput(1,6);
    return am_option;
}

static inline int lecturer_management_menu(){
    int lm_option;
    system("cls");
    cout<<"============ Lecturer Management Menu =================\n";
    cout<<"1. Add Lecturer\n";
    cout<<"2. Lecturer Assignment\n";
    cout<<"3. Search Lecturer\n";
    cout<<"4. View all Lecturers\n";
    cout<<"5. Edit Lecturer Details\n";
    cout<<"6. Delete Lecturer\n";
    cout<<"7. Back\n";
    cout<<"Enter option: ";
    lm_option = validateInput(1,7);
    return lm_option;
}

static inline int lecturer_assignment_menu(){
    int lam_option;
    system("cls");
    cout<<"============ Lecturer Management Menu =================\n";
    cout<<"1. Assign Lecturer\n";
    cout<<"2. View Lecturer's Courses\n";
    cout<<"3. View Course Lecturer\n";
    cout<<"4. Remove Lecturer Assignment\n";
    cout<<"5. Exit\n";
    cout<<"Enter option: ";
    lam_option = validateInput(1,5);
    return lam_option;
}
static inline int registration_menu(){
    int r_option;
    system("cls");
    cout<<"============ Course Registration =================\n";
    cout<<"1. View Available Courses\n";
    cout<<"2. Register for Course\n";
    cout<<"3. View Registered Courses\n";
    cout<<"4. Drop Course\n";
    cout<<"5. Back\n";
    cout<<"Enter option: ";
    r_option = validateInput(1,5);
    return r_option;
}

static inline int course_options_menu(){
    int co_option;
    system("cls");
    cout<<"============ Course Options =================\n";
    cout<<"1. Toggle Assignements\n";
    cout<<"2. Enter CA Marks\n";
    cout<<"3. Enter Final Exam Marks\n";
    cout<<"4. Back\n";
    cout<<"Enter option: ";
    co_option = validateInput(1,4);
    return co_option;
}


#endif
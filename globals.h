#ifndef GlOBALS_H
#define GlOBALS_H

#include <iostream>
#include "auth.h"
#include <limits>
#include <string>
#include "menus.h"
#include "admin_logic.h"
#include "students.h"
#include "courses.h"
#include "lecturer.h"
#include "students_crud.h"
#include "assignment.h"
#include "lecturer_crud.h"
#include "registration.h"
#include <fstream>
#include <unistd.h> 
using namespace std;

class Student{
public:
    string name, program, email, password;
    int age, phone_number, year_of_study;
    int studentID = 260001;
    char gender;
    float grades[6];  

    Student() {
        for(int i = 0; i < 6; i++) {
            grades[i] = 0.0;
        }
    }
    
};

class Course{
public:
    string course_code, course_name, course_program;
    int year_offered;
    int lecturerID = -1;

};

class Lecturer{
public:
    int lecturerID;
    string name, email, password, phone_number, department;
};

class Registration{
public:
    int studentID;
    string course_code;
};

extern Student students[100];
extern int student_count;
extern int next_student_id;
extern Course course[100];
extern int course_count;
extern Lecturer lecturer[100];
extern int lecturer_count;
extern int next_lecturer_id;
extern Registration registrations[500];
extern int registration_count;

#endif
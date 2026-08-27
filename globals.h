#ifndef GlOBALS_H
#define GlOBALS_H

#include <iostream>
#include "auth.h"
#include <limits>
#include <string>
#include "auth.h"
#include "menus.h"
#include "validation.h"
#include "admin_logic.h"
#include "students.h"
#include "courses.h"
#include "lecturer.h"
#include "students_crud.h"
#include "assignment.h"
#include "lecturer_crud.h"
#include "registration.h"
#include "results.h"
#include <fstream>
#include <unistd.h> 
using namespace std;

class Student{
public:
    string name, program, email, password, phone_number;
    int age, year_of_study;
    int studentID = 260001;
    char gender;
    Student() {}
    
};

class Course{
public:
    string course_code, course_name, course_program;
    int year_offered;
    int lecturerID = -1;
    bool has_assignement = false;

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

class Results{
public: 
    int studentID;
    string course_code;
    float test1 = 0.0;
    float test2 = 0.0;
    float assignment = 0.0;
    float continousAssessment = 0.0;
    float finalExam = 0.0;
    float finalMark = 0.0;
    string finalGrade = "";
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
extern Results results[500];
extern int result_count;

#endif
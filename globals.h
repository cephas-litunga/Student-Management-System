#ifndef GLOBALS_H
#define GLOBALS_H

#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <cctype>
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
#include <unistd.h>

using namespace std;

constexpr int MAX_STUDENTS = 100;
constexpr int MAX_COURSES = 100;
constexpr int MAX_LECTURERS = 100;
constexpr int MAX_REGISTRATIONS = 500;
constexpr int MAX_RESULTS = 500;

constexpr const char* ADMIN_PASSWORD = "admin123";

class Student{
public:
    string name, program, email, password, phone_number;
    int age = 0, year_of_study = 1;
    int studentID = 260001;
    char gender = ' ';
};

class Course{
public:
    string course_code, course_name, course_program;
    int year_offered = 0;
    int lecturerID = -1;
    bool has_assignement = false;
};

class Lecturer{
public:
    int lecturerID = 0;
    string name, email, password, phone_number, department;
};

class Registration{
public:
    int studentID = 0;
    string course_code;
};

class Results{
public:
    int studentID = 0;
    string course_code;
    float test1 = 0.0;
    float test2 = 0.0;
    float assignment = 0.0;
    float continousAssessment = 0.0;
    float finalExam = -1.0;
    float finalMark = -1.0;
    string finalGrade = "";
};

extern Student students[MAX_STUDENTS];
extern int student_count;
extern int next_student_id;

extern Course course[MAX_COURSES];
extern int course_count;

extern Lecturer lecturer[MAX_LECTURERS];
extern int lecturer_count;
extern int next_lecturer_id;

extern Registration registrations[MAX_REGISTRATIONS];
extern int registration_count;

extern Results results[MAX_RESULTS];
extern int result_count;

#endif

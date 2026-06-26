#ifndef GlOBALS_H
#define GlOBALS_H

#include <iostream>
#include "auth.h"
#include <limits>
#include <string>
#include "menus.h"
#include "admin_logic.h"
#include "students.h"
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

extern Student students[100];
extern int student_count;
extern int next_student_id;

#endif
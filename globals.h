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
    string name;
    int age;
    string program;
    float grades[6];  
    Student() {
        for(int i = 0; i < 6; i++) {
            grades[i] = 0.0;
        }
    }
    int studentID = 260000;
    string password;
    string email;
    int phone_number;
    int year_of_study;
};

extern Student students[100];
extern int student_count;
extern int next_student_id;

#endif
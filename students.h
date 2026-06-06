#ifndef STUDENTS_H
#define STUDENTS_H

#include <string>
using namespace std;

class Student{
public:
    string name;
    int age;
    string program;
    float grades[6];  // Array to store grades for 6 subjects
    Student() {
        for(int i = 0; i < 6; i++) {
            grades[i] = 0.0;
        }
    }
    int studentID = 260000;
};

void add_students();
void search_students();
void edit_student_grades();
void edit_student_details();
void view_all_students();
void view_student_grades();
void delete_student();



#endif
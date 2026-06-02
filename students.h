#ifndef STUDENTS_H
#define STUDENTS_H

using namespace std;

class Student{
public:
    string name;
    int age;
    string program;
};

void add_students();
void search_students();
void edit_student_details();
void view_all_students();
void edit_grades();



#endif
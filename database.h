#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include "globals.h"
#include <vector>

bool initialize_database();
void close_database();
bool insert_student(const Student& student);
bool insert_lecturer(const Lecturer& lecturer);
bool insert_course(const Course& course);
bool register_student(int student_id,  const string& course_code);
void view_registrations();
bool insert_result(const Results& result);
bool is_student_registered(int student_id, const string& course_code);
int get_result_status(int student_id);
void view_student_results(int student_id);
void delete_test_result(int student_id, const string& course_code);
void view_all_results();

vector<Student> get_students();
vector<string> get_student_courses(int student_id);
#endif
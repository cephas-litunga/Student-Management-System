#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include "globals.h"
#include <vector>

bool initialize_database();
void close_database();

bool insert_student(const Student& student);
bool update_student(const Student& student);
bool delete_student(int student_id);

bool insert_lecturer(const Lecturer& lecturer);
bool update_lecturer(const Lecturer& lecturer);
bool delete_lecturer(int lecturer_id);

bool insert_course(const Course& course);
bool update_course(const Course& course);
bool delete_course(const string& course_code);

bool register_student(int student_id,  const string& course_code);
bool delete_registration(int student_id, const string& course_code);

bool save_result(const Results& result);
bool update_student_password(int student_id, const string& new_password); 
bool update_lecturer_password(int lecturer_id, const string& new_password);

void view_registrations();
bool insert_result(const Results& result);
bool is_student_registered(int student_id, const string& course_code);
int get_result_status(int student_id);
void view_student_results(int student_id);
void delete_test_result(int student_id, const string& course_code);
void view_all_results();

vector<Student> get_students();
vector<Lecturer> get_lecturers();
vector<Course> get_courses();
vector<Registration> get_registrations();
vector<Results> get_results();
vector<string> get_student_courses(int student_id);
#endif
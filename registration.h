#ifndef REGISTRATION_H
#define REGISTRATION_H

void view_available_courses(int student_index);
void register_course(int student_index);
void view_registered_courses(int student_index);
void drop_course(int student_index);
void save_registrations();
void load_registrations();

#endif
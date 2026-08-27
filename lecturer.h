#ifndef LECTURER_H
#define LECTURER_H

void view_lecturer_details(int lecturer_index);
void update_lecturer_info(int lecturer_index);
void change_lecturer_password(int lecturer_index);
void view_assigned_courses(int lecturer_index);
void toggle_assignment(int lecturer_index, int course_index);
void manage_results(int lecturer_index);
void enter_ca_marks(int lecturer_index, int course_index);
void enter_final_exam(int lecturer_index, int course_index);

void enter_results(int lecturer_index, int course_index);
#endif
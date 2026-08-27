#ifndef RESULTS_H
#define RESULTS_H

void enter_ca_marks(int lecturer_index, int course_index);
void enter_final_exam(int lecturer_index, int course_index);
void save_results();
void load_results();
string assign_grade(float final_mark);
float calculate_test_CA(float score, float total, bool has_assignment);
float calculate_assignment_CA(float score);

#endif
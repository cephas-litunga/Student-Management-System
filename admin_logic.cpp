#include "globals.h"

Student students[MAX_STUDENTS];
int student_count = 0;
int next_student_id = 260001;

Lecturer lecturer[MAX_LECTURERS];
int lecturer_count = 0;

void student_management(){
    system("cls");
    while(1){
        int st_option = student_management_menu();
        switch(st_option){
            case 1: add_student(); break;
            case 2: search_student(); break;
            case 3: view_all_students(); break;
            case 4: edit_student_details(); break;
            case 5: delete_student(); break;
            case 6: save_students(); return;
            default: cout<<"Invalid Option! Please try again.\n"; system("pause"); break;
        }
    }
}

void course_management(){
    system("cls");
    while(1){
        int option = course_management_menu();
        system("cls");
        switch(option){
            case 1: add_course(); break;
            case 2: view_all_courses(); break;
            case 3: delete_course(); break;
            case 4: search_course(); break;
            case 5: edit_course(); break;
            case 6: cout<<"Exiting!\n"; save_courses(); return;
            default: cout<<"Invalid option! Please try again.\n"; system("pause");
        }
    }
}

void lecturer_management(){
    system("cls");
    while(1){
        int option = lecturer_management_menu();
        system("cls");
        switch(option){
            case 1: register_lecturer(); break;
            case 2: lecturer_assignment(); break;
            case 3: search_lecturer(); break;
            case 4: view_all_lecturers(); break;
            case 5: edit_lecturer(); break;
            case 6: delete_lecturer(); break;
            case 7: save_lecturers(); return;
            default: cout<<"Invalid option! Please try again.\n"; system("pause");
        }
    }
}

void lecturer_assignment(){
    system("cls");
    while(1){
        int option = lecturer_assignment_menu();
        system("cls");
        switch(option){
            case 1: assign_lecturer(); break;
            case 2: view_lecturer_courses(); break;
            case 3: view_course_lecturer(); break;
            case 4: remove_lecturer_assignment(); break;
            case 5: return;
            default: cout<<"Invalid option! Please try again.\n"; system("pause");
        }
    }
}

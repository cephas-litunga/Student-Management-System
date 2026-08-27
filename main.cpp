#include "globals.h"

// compile commmand: g++ main.cpp auth.cpp admin_logic.cpp students_crud.cpp lecturer_crud.cpp assignment.cpp courses.cpp students.cpp lecturer.cpp registration.cpp -o main
// Check registration validation, can skip details and proceed
// When student gets removed, their registration should be removed aswell
// Only view final grade when all have been entered
// Show all registered courses CA, if not yet applicable then display 0
using namespace std;

int main(){
    int menu_choice;
    load_students();
    load_courses();
    load_lecturers();
    load_registrations();
    load_results();
    while(1){
        menu_choice = home_menu();
        switch(menu_choice){
            case 1: login(); break;
            case 2: cout<<"Exiting...\n"; save_students(); save_courses(); save_lecturers(); save_registrations(); save_results(); return 0;
            default: cout<<"Invalid option! Please try again.\n"; system("pause");
        }
    }
}
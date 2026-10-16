#include "globals.h"
#include "database.h"

// compile command: g++ main.cpp auth.cpp admin_logic.cpp students_crud.cpp lecturer_crud.cpp assignment.cpp courses.cpp students.cpp lecturer.cpp registration.cpp -o main
// Check registration validation, can skip details and proceed
// When student gets removed, their registration should be removed as well
// Only view final grade when all have been entered
// Show all registered courses CA, if not yet applicable then display 0
using namespace std;




int main(){

    int menu_choice;
    if(!initialize_database()) { return 1; }
    load_students_from_database();
    load_courses_from_database();
    load_lecturers_from_database();
    load_registrations_from_database();
    load_results_from_database();
    while(1){
        menu_choice = home_menu();
        switch(menu_choice){
            case 1: login(); break;
            case 2: cout<<"Exiting...\n"; close_database(); return 0;
            default: cout<<"Invalid option! Please try again.\n"; system("pause");
        }
    }
}
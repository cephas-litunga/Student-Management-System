#include <iostream>
#include "menus.h"
#include "students.h"

using namespace std;

int main(){
    int menu_choice;
    while(1){
        menu_choice = main_menu();
        switch(menu_choice){
            case 1: add_students();
                break;
            case 2: search_students();
                break;
            case 3: view_all_students();
                break;
            case 4: edit_student_grades();
                break;
            case 5: edit_student_details();
                break;
            case 6: view_student_grades();
                break;
            case 7: delete_student();
                break;
            case 8: cout<<"Exiting...\n";
                break;
            default: cout<<"ERROR!\n";
                break;
        }
    }
    return 0;
}
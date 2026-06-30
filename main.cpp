#include "globals.h"

// compile commmand: g++ main.cpp auth.cpp admin_logic.cpp students.cpp courses.cpp -o main

using namespace std;

int main(){
    int menu_choice;
    load_students();
    load_courses();
    while(1){
        menu_choice = home_menu();
        switch(menu_choice){
            case 1: login(); break;
            case 2: cout<<"Exiting...\n"; save_students(); save_courses(); return 0;
            default: cout<<"Invalid option! Please try again.\n"; system("pause");
        }
    }
}
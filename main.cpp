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
            case 4: cout<<"coming soon!\n";
                break;
            case 5: cout<<"coming soon!\n";
                break;
            case 6: cout<<"coming soon!\n";
                break;
            case 7: cout<<"Exiting\n";
                return 0;
            default: cout<<"ERROR!\n";
                break;
        }
    }
    return 0;
}
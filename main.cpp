#include <iostream>
#include "menus.h"
using namespace std;

int main(){
    int menu_choice;
    while(1){
        menu_choice = main_menu();
        switch(menu_choice){
            case 1: cout<<"coming soon!\n";
                break;
            case 2: cout<<"coming soon!\n";
                break;
            case 3: cout<<"coming soon!\n";
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
        }
    }

    return 0;
}
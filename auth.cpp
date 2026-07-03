#include "globals.h"
using namespace std;

void login(){
    int option = login_menu();
    if (option == 1) {
        if(admin_login() == 1){
            while(1){
                int am_option = admin_menu();
                switch (am_option){
                    case 1: student_management(); break;
                    case 2:{ cout<<"lecturer Management Coming soon!\n"; system("pause"); break;}
                    case 3: course_management(); break;
                    case 4: cout<<"Logging out...\n"; save_students(); save_courses(); system("pause"); return;
                    default: cout<<"Invalid option! Please try again.\n"; system("pause"); break;
                }
            }
        }
    }
    else if (option == 2){
        int current_student = student_login();
        if(current_student != -1){
            while(1){
                int s_option = student_menu();
                switch (s_option){
                    case 1: view_grades(current_student); break;
                    case 2: view_details(current_student); break;
                    case 3: update_info(current_student); break;
                    case 4: cout<<"Logging out...\n"; save_students(); save_courses(); system("pause"); return;
                    default: cout<<"Invalid option! Please try again.\n"; system("pause"); break;
                }
            }
        }
    }
    else if (option == 3) return;
    else cout<<"Invalid option! Please try again.\n";
          
}

bool admin_login(){
    system("cls");
    const string username = "admin";
    const string password = "admin123";
    string input_username, input_password;
    bool accepted = false;
    cout<<"===== Admin Login =====\n";
    cout<<"Username: ";
    getline(cin, input_username);
    cout<<"Password: ";
    getline(cin, input_password);
    
    if(input_username == username && input_password == password){
        system("cls");
        cout<<"===== Admin Login =====\n";
        cout<<"Login successful!\n";
        accepted = true;
        system("pause");
    } else {
        system("cls");
        cout<<"===== Admin Login =====\n";
        cout<<"Invalid username or password.\n";
        system("pause");
    }
    return accepted;
}


int student_login(){
    system("cls");
    int student_id;
    string password;
    cout<<"===== Student Login =====\n";
    cout<<"Enter Student ID: ";
    cin>>student_id;
    cin.ignore(); // Ignore the newline character left in the buffer
    cout<<"Enter password: ";
    getline(cin, password);

    for(int i = 0; i < student_count; i++){
        if(students[i].studentID == student_id && students[i].password == password){
            system("cls");
            cout<<"===== Student Login =====\n";
            cout<<"Login successful!\n";
            cout<<"Welcome, "<<students[i].name<<"!\n";
            system("pause");
            return i;
        }
    }

    system("cls");
    cout<<"===== Student Login =====\n";
    cout<<"Invalid student ID or password.\n";
    system("pause");
    return -1;
}
    


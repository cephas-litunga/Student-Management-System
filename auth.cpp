#include "globals.h"

void login(){
    int option = login_menu();

    if(option == 1){
        if(admin_login()){
            while(1){
                int am_option = admin_menu();

                switch(am_option){
                    case 1: student_management(); break;
                    case 2: lecturer_management(); break;
                    case 3: course_management(); break;
                    case 4:
                        cout<<"Logging out...\n";
                        system("pause");
                        return;
                    default:
                        cout<<"Invalid option! Please try again.\n";
                        break;
                }
            }
        }
    }
    else if(option == 2){
        int current_student = student_login();

        if(current_student != -1){
            while(1){
                int s_option = student_menu();

                switch(s_option){
                    case 1: view_details(current_student); break;
                    case 2: view_ca(current_student); break;
                    case 3: view_grades(current_student); break;
                    case 4: update_info(current_student); break;
                    case 5: change_password(current_student); break;
                    case 6: student_register_course(current_student); break;
                    case 7:
                        cout<<"Logging out...\n";
                        save_students();
                        save_courses();
                        save_registrations();
                        save_results();
                        system("pause");
                        return;
                    default:
                        cout<<"Invalid option! Please try again.\n";
                        system("pause");
                        break;
                }
            }
        }
    }
    else if(option == 3){
        int current_lecturer = lecturer_login();

        if(current_lecturer != -1){
            while(1){
                int l_option = lecturer_menu();

                switch(l_option){
                    case 1: view_lecturer_details(current_lecturer); break;
                    case 2: update_lecturer_info(current_lecturer); break;
                    case 3: change_lecturer_password(current_lecturer); break;
                    case 4: view_assigned_courses(current_lecturer); break;
                    case 5: manage_results(current_lecturer); break;
                    case 6:
                        cout<<"Logging out...\n";
                        save_lecturers();
                        save_results();
                        system("pause");
                        return;
                    default:
                        cout<<"Invalid option! Please try again.\n";
                        system("pause");
                        break;
                }
            }
        }
    }
    else{
        cout<<"Invalid option! Please try again.\n";
    }
}

bool admin_login(){
    system("cls");

    const string username = "admin";
    string input_username;
    string input_password;

    cout<<"===== Admin Login =====\n";
    cout<<"Username: ";
    getline(cin, input_username);

    int attempts = 0;

    while(attempts < 3){
        cout<<"Password: ";
        getline(cin, input_password);

        if(input_username == username &&
           input_password == ADMIN_PASSWORD){
            system("cls");
            cout<<"===== Admin Login =====\n";
            cout<<"Login successful!\n";
            system("pause");
            return true;
        }

        attempts++;

        if(attempts < 3)
            cout<<"Invalid credentials. "
                <<3 - attempts<<" attempt(s) remaining.\n";
    }

    system("cls");
    cout<<"===== Admin Login =====\n";
    cout<<"Too many failed attempts. Access Denied.\n";
    system("pause");

    return false;
}

int student_login(){
    system("cls");

    int student_id;
    int attempts = 0;
    string password;

    cout<<"===== Student Login =====\n";
    cout<<"Enter Student ID: ";

    if(!(cin>>student_id)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"Invalid student ID.\n";
        system("pause");
        return -1;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while(attempts < 3){
        cout<<"Enter password: ";
        getline(cin, password);

        for(int i = 0; i < student_count; i++){
            if(students[i].studentID == student_id &&
               students[i].password == password){
                system("cls");
                cout<<"===== Student Login =====\n";
                cout<<"Login successful!\n";
                cout<<"Welcome, "<<students[i].name<<"!\n";
                system("pause");
                return i;
            }
        }

        attempts++;

        if(attempts < 3)
            cout<<"Invalid credentials. "
                <<3 - attempts<<" attempt(s) left.\n";
    }

    system("cls");
    cout<<"===== Student Login =====\n";
    cout<<"Too many failed attempts. Access denied.\n";
    system("pause");

    return -1;
}

int lecturer_login(){
    system("cls");

    int lecturer_id;
    int attempts = 0;
    string password;

    cout<<"===== Lecturer Login =====\n";
    cout<<"Enter Lecturer ID: ";

    if(!(cin>>lecturer_id)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"Invalid lecturer ID.\n";
        system("pause");
        return -1;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while(attempts < 3){
        cout<<"Enter password: ";
        getline(cin, password);

        for(int i = 0; i < lecturer_count; i++){
            if(lecturer[i].lecturerID == lecturer_id &&
               lecturer[i].password == password){
                system("cls");
                cout<<"===== Lecturer Login =====\n";
                cout<<"Login successful!\n";
                cout<<"Welcome, "<<lecturer[i].name<<"!\n";
                system("pause");
                return i;
            }
        }

        attempts++;

        if(attempts < 3)
            cout<<"Invalid credentials. "
                <<3 - attempts<<" attempt(s) remaining.\n";
    }

    system("cls");
    cout<<"===== Lecturer Login =====\n";
    cout<<"Too many failed attempts. Access denied.\n";
    system("pause");

    return -1;
}

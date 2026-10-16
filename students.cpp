#include "globals.h"
#include "database.h"
// Student Portal Functions
void view_details(int index){
    system("cls");
    cout<<"==================== Student Details ====================\n";
    cout<<"Name: "<<students[index].name<<endl;
    cout<<"Age: "<<students[index].age<<endl;
    cout<<"Program: "<<students[index].program<<endl;
    cout<<"Student ID: "<<students[index].studentID<<endl;
    cout<<"Email: "<<students[index].email<<endl;
    cout<<"Phone Number: "<<students[index].phone_number<<endl;
    system("pause");
}

void view_grades(int index){
    system("cls");
    cout<<"==================== My Grades ====================\n";
    bool found = false;
    for(int i = 0; i < result_count; i++){
        if(results[i].studentID == students[index].studentID){
            if(results[i].finalGrade != ""){
                cout<<results[i].course_code<<" - "<<results[i].finalGrade<<endl;
                found = true;
            }
        }
    }

    if(!found) cout<<"No grades available yet.\n";
    system("pause");
}


void view_ca(int index){
    system("cls");
    cout<<"==================== My CA ====================\n";
    bool found = false;
    for(int i = 0; i < result_count; i++){
        if(results[i].studentID == students[index].studentID){
            cout<<results[i].course_code<<" -  "<<results[i].continuousAssessment<<endl;
            found = true;
        }
    }
    if(!found) cout<<"No CA results available yet.\n";
    system("pause");

}


void change_password(int index){
    system("cls");

    string new_password, current_password;

    cout << "==================== Change Password ====================\n";
    cout << "Enter current password: ";
    getline(cin, current_password);

    while(current_password != students[index].password){
        cout << "Incorrect current password!\n";
        cout << "Enter current password: ";
        getline(cin, current_password);
    }

    new_password = validatePassword("Enter new password: ");

    if(!update_student_password(students[index].studentID, new_password)){
        cout << "Password change failed. Please try again.\n";
        system("pause");
        return;
    }

    students[index].password = new_password;

    cout << "Password changed successfully!\n";
    system("pause");
}



void update_info(int index){
    system("cls");

    int option;

    cout << "==================== Update Student Info ====================\n";
    cout << "1. Update Phone number\n";
    cout << "2. Update Email\n";
    cout << "3. Change password\n";
    cout << "Enter option: ";

    if(!(cin >> option)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid option!\n";
        system("pause");
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if(option == 3){
        change_password(index);
        return;
    }

    if(option != 1 && option != 2){
        cout << "Invalid option! Please try again.\n";
        system("pause");
        return;
    }

    Student previous_student = students[index];

    if(option == 1){
        students[index].phone_number =
            validatePhone("Enter new phone number: ");
    }else{
        students[index].email =
            validateEmail("Enter new email: ");
    }

    if(!update_student(students[index])){
        students[index] = previous_student;

        cout << "Failed to update information in the database.\n";
        system("pause");
        return;
    }

    cout << "Student information updated successfully!\n";
    system("pause");
}


void student_register_course(int index){
    system("cls");
    while(1){
        int r_option = registration_menu();
        system("cls");
        switch (r_option){
            case 1: view_available_courses(index); break;
            case 2: register_course(index); break;
            case 3: view_registered_courses(index); break;
            case 4: drop_course(index); break;
            case 5: cout<<"Returning to previous menu...\n"; system("pause"); return;
            default: cout<<"Invalid option! Please try again.\n"; system("pause"); break;
        }
    }
}
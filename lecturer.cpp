#include "globals.h"

void view_lecturer_details(int lecturer_index){
    system("cls");
    cout<<"==================== Lecturer Details ====================\n";
    cout<<"Name: "<<lecturer[lecturer_index].name<<endl;
    cout<<"Email: "<<lecturer[lecturer_index].email<<endl;
    cout<<"Phone Number: "<<lecturer[lecturer_index].phone_number<<endl;
    cout<<"Lecturer ID: "<<lecturer[lecturer_index].lecturerID<<endl;
    system("pause");
}

void update_lecturer_info(int lecturer_index){
    system("cls");
    cout<<"==================== Update Lecturer Info ====================\n";
    lecturer[lecturer_index].email = validateEmail("Enter Email: ");
    lecturer[lecturer_index].phone_number = validatePhone("Enter Phone Number: ");
    cout<<"Lecturer Details updated successfully!\n";
    system("pause");
}

void change_lecturer_password(int lecturer_index){
    system("cls");
    cout<<"==================== Change Lecturer Password ====================\n";
    string current_password;
    cout<<"Enter Current password: ";
    getline(cin, current_password);

    while(current_password != lecturer[lecturer_index].password){
        cout<<"Incorrect password entered. Try again\n";
        cout<<"Enter Current password: ";
        getline(cin, current_password);
    }
    lecturer[lecturer_index].password = validatePassword("Enter new password");
    cout<<"Password changed successfully!\n";
    system("pause");
}

void view_assigned_courses(int lecturer_index){
    system("cls");
    bool found = false;
    cout<<"================= Courses ======================\n";
    for(int i = 0; i < course_count; i++){
        if(course[i].lecturerID == lecturer[lecturer_index].lecturerID){
            cout<<"Code: "<<course[i].course_code<<endl;
            cout<<"Name: "<<course[i].course_name<<endl;
            cout<<"Program: "<<course[i].course_program<<endl;
            cout<<"Year: "<<course[i].year_offered<<endl;
            cout<<"_______________________________________________\n";
            found = true;
        }
    }
    if(!found) cout<<"You have no courses assigned.\n";
    system("pause");
}

void toggle_assignment(int lecturer_index, int course_index){
    system("cls");
    course[course_index].has_assignement = !course[course_index].has_assignement;
    cout<<"Assignment "<<(course[course_index].has_assignement ? "Enabled" : "Disabled")
    <<" for "<<course[course_index].course_code<<".\n";
    save_courses();
    system("pause");
}
    


void manage_results(int lecturer_index){
    system("cls");
    string course_code;
    bool has_courses = false;
    cout<<"================= Manage Courses ======================\n";
    for(int i = 0; i < course_count; i++){
        if(course[i].lecturerID == lecturer[lecturer_index].lecturerID){
            cout<<"Code: "<<course[i].course_code<<endl;
            cout<<"Name: "<<course[i].course_name<<endl;     
            cout<<"Has Assignment: "<<(course[i].has_assignement ? "Yes" : "No")<<endl;
            cout<<"_______________________________________________"<<endl;
            has_courses = true;
        }
    }

    if(!has_courses){
        cout<<"You have no assigned courses!\n";
        system("pause");
        return;
    }
    cout<<"Enter course code: ";
    getline(cin, course_code);
    
    int course_index = -1;
    for(int i = 0; i < course_count; i++){
        if (course[i].course_code == course_code && course[i].lecturerID == lecturer[lecturer_index].lecturerID){
            course_index = i;
            break;
        }
    }
    
    if(course_index == -1){
        cout<<"Course not found or not assigned to you!\n";
        system("pause");
        return;
    }

    while(1){
        int option = course_options_menu();
        switch(option){
            case 1: toggle_assignment(lecturer_index, course_index); break;
            case 2: enter_ca_marks(lecturer_index, course_index); break;
            case 3: enter_final_exam(lecturer_index, course_index); break;
            case 4: return;
            default: cout<<"invalid option.\n"; system("pause"); break;
        }
    }
}

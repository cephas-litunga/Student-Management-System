#include "globals.h"

int next_lecturer_id = 1000;

// Lecturer assignment functions
void assign_lecturer(){
    int lecturer_id;
    string course_code;
    system("cls");
    cout<<"============ Lecturer Course Assignment =================\n";
    cout<<"Enter Course Code to Assign: ";
    getline(cin, course_code);

    // Find the course
    int course_index = -1;
    for(int i = 0; i < course_count; i++){
        if(course[i].course_code == course_code){
            course_index = i;
            break;
        }
    }
    if(course_index == -1){
        cout<<"Course "<<course_code<<" not found!\n";
        system("pause");
        return;
    }

    // Check if already assigned
    if(course[course_index].lecturerID != -1){
        string assigned_name = "";
        for(int i = 0; i < lecturer_count; i++){
            if(lecturer[i].lecturerID == course[course_index].lecturerID){
                assigned_name = lecturer[i].name;
                break;
            }
        }
        cout<<"Course "<<course_code<<" is already assigned to "<<assigned_name<<".\n";
        cout<<"1. Replace assignment\n";
        cout<<"2. Cancel\n";
        cout<<"Enter option: ";
        int choice = validateInput(1, 2);
        if(choice == 2){
            cout<<"Assignment cancelled.\n";
            system("pause");
            return;
        }
    }

    cout<<"Enter Lecturer ID: ";
    cin>>lecturer_id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Find the lecturer
    int lecturer_index = -1;
    for(int i = 0; i < lecturer_count; i++){
        if(lecturer[i].lecturerID == lecturer_id){
            lecturer_index = i;
            break;
        }
    }
    if(lecturer_index == -1){
        cout<<"Lecturer with ID "<<lecturer_id<<" not found!\n";
        system("pause");
        return;
    }

    course[course_index].lecturerID = lecturer[lecturer_index].lecturerID;
    cout<<"Lecturer "<<lecturer[lecturer_index].name<<" assigned to "<<course[course_index].course_code<<" successfully!\n";
    save_courses();
    system("pause");
}

void view_lecturer_courses(){
    int lecturer_id;
    system("cls");
    bool found = false;
    cout<<"============ Lecturer Course Assignment =================\n";
    cout<<"Enter Lecturer ID: ";
    cin >> lecturer_id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    string lecturer_name = "";
    for(int i = 0; i < lecturer_count; i++){
        if(lecturer[i].lecturerID == lecturer_id){
            lecturer_name = lecturer[i].name;
            break;
        }
    }

    system("cls");
    cout<<"================= Courses ======================\n";
    for(int i = 0; i < course_count; i++){
        if(course[i].lecturerID == lecturer_id){
            cout << course[i].course_code << " - " << lecturer_name << endl;
            found = true;
        }
    }
    if(!found) cout<<"No courses assigned to this lecturer\n";
    system("pause");
}

void view_course_lecturer(){
    system("cls");
    string course_code;
    cout<<"============ View Course Lecturer =================\n";
    cout<<"Enter course code: ";
    getline(cin, course_code);

    int course_index = -1;
    for(int i = 0; i < course_count; i++){
        if(course_code == course[i].course_code){
            course_index = i;
            break;
        }
    }
    if(course_index == -1){
        cout<<"Course "<<course_code<<" not found!\n";
        system("pause");
        return;
    }
    if(course[course_index].lecturerID == -1){
        cout<<"No lecturer assigned to "<<course_code<<".\n";
        system("pause");
        return;
    }

    for(int j = 0; j < lecturer_count; j++){
        if(lecturer[j].lecturerID == course[course_index].lecturerID){
            cout<<"Name: "<<lecturer[j].name<<endl;
            cout<<"Department: "<<lecturer[j].department<<endl;
            cout<<"Email: "<<lecturer[j].email<<endl;
            cout<<"Phone Number: "<<lecturer[j].phone_number<<endl;
            break;
        }
    }
    system("pause");
}

void remove_lecturer_assignment(){
    system("cls");
    string course_code;
    cout<<"============ Remove Lecturer Assignment =================\n";
    cout<<"Enter course code: ";
    getline(cin, course_code);

    int course_index = -1;
    for(int i = 0; i < course_count; i++){
        if(course[i].course_code == course_code){
            course_index = i;
            break;
        }
    }
    if(course_index == -1){
        cout<<"Course "<<course_code<<" not found!\n";
        system("pause");
        return;
    }
    if(course[course_index].lecturerID == -1){
        cout<<"Course "<<course_code<<" has no lecturer assigned.\n";
        system("pause");
        return;
    }

    // Find lecturer name for confirmation message
    string lecturer_name = "";
    for(int i = 0; i < lecturer_count; i++){
        if(lecturer[i].lecturerID == course[course_index].lecturerID){
            lecturer_name = lecturer[i].name;
            break;
        }
    }

    cout<<"Remove "<<lecturer_name<<" from "<<course_code<<"?\n";
    cout<<"1. Confirm\n";
    cout<<"2. Cancel\n";
    cout<<"Enter option: ";
    int choice = validateInput(1, 2);
    if(choice == 2){
        cout<<"Removal cancelled.\n";
        system("pause");
        return;
    }
    
    sleep(1);

    course[course_index].lecturerID = -1;
    cout<<"Lecturer removed from "<<course_code<<" successfully!\n";
    save_courses();
    system("pause");
}
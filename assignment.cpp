#include "globals.h"
#include "database.h"


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

    int previous_lecturer_id = course[course_index].lecturerID;

    course[course_index].lecturerID =
    lecturer[lecturer_index].lecturerID;

    if(!update_course(course[course_index])){
        // Restore the original in-memory assignment if the database update fails.
        course[course_index].lecturerID = previous_lecturer_id;

        cout<<"Failed to save lecturer assignment to the database.\n";
        system("pause");
        return;
    }

    cout<<"Lecturer "<<lecturer[lecturer_index].name
    <<" assigned to "<<course[course_index].course_code
    <<" successfully!\n";

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

    cout << "============ Remove Lecturer Assignment ============\n";
    cout << "Enter Course Code: ";

    string course_code;
    getline(cin, course_code);

    // Find the course.
    int course_index = -1;

    for(int i = 0; i < course_count; i++){
        if(course[i].course_code == course_code){
            course_index = i;
            break;
        }
    }

    if(course_index == -1){
        cout << "Course " << course_code << " not found!\n";
        system("pause");
        return;
    }

    // Check whether a lecturer is assigned.
    int current_lecturer_id = course[course_index].lecturerID;

    if(current_lecturer_id == -1){
        cout << "This course has no assigned lecturer.\n";
        system("pause");
        return;
    }

    string lecturer_name = "Unknown lecturer";

    for(int i = 0; i < lecturer_count; i++){
        if(lecturer[i].lecturerID == current_lecturer_id){
            lecturer_name = lecturer[i].name;
            break;
        }
    }

    cout << "Remove " << lecturer_name
         << " from course " << course_code << "?\n";
    cout << "1. Confirm\n";
    cout << "2. Cancel\n";
    cout << "Enter option: ";

    if(validateInput(1, 2) == 2){
        cout << "Removal cancelled.\n";
        system("pause");
        return;
    }

    // Remove the assignment in memory.
    course[course_index].lecturerID = -1;

    // Persist the change in SQLite.
    if(!update_course(course[course_index])){
        course[course_index].lecturerID = current_lecturer_id;

        cout << "Failed to remove lecturer assignment from database.\n";
        system("pause");
        return;
    }

    cout << "Lecturer assignment removed successfully.\n";
    system("pause");
}
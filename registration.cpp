#include "globals.h"
using namespace std;

Registration registrations[500];
int registration_count = 0;

void view_available_courses(int student_index){
    system("cls");
    cout<<"=================== Available Courses ===================\n";
    bool found = false;
    for(int i = 0; i < course_count; i++){
        if(course[i].course_program == students[student_index].program &&
           course[i].year_offered <= students[student_index].year_of_study){
            cout<<"Code: "<<course[i].course_code<<endl;
            cout<<"Name: "<<course[i].course_name<<endl;
            cout<<"Year: "<<course[i].year_offered<<endl;
            cout<<"________________________________________________\n";
            found = true;
        }
    }
    if(!found) cout<<"No available courses for your program and year.\n";
    system("pause");
}

void register_course(int student_index){
    system("cls");
    cout<<"=================== Course Registration ===================\n";

    if(registration_count >= 500){
        cout<<"Registration system is full.\n";
        system("pause");
        return;
    }

    cout<<"Enter Course Code: ";
    string course_code;
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

    // Program validation
    if(course[course_index].course_program != students[student_index].program){
        cout<<"You cannot register for this course.\n";
        cout<<"This course is for "<<course[course_index].course_program<<" students.\n";
        system("pause");
        return;
    }

    // Year validation
    if(course[course_index].year_offered > students[student_index].year_of_study){
        cout<<"You cannot register for this course.\n";
        cout<<"This is a Year "<<course[course_index].year_offered<<" course. You are in Year "<<students[student_index].year_of_study<<".\n";
        system("pause");
        return;
    }

    // Check if already registered
    for(int i = 0; i < registration_count; i++){
        if(registrations[i].studentID == students[student_index].studentID &&
            registrations[i].course_code == course_code){
            cout<<"You are already registered for "<<course_code<<".\n";
            system("pause");
            return;
        }
    }

    // Register
    registrations[registration_count].studentID = students[student_index].studentID;
    registrations[registration_count].course_code = course_code;
    registration_count++;
    cout<<"Successfully registered for "<<course[course_index].course_name<<"!\n";
    save_registrations();
    system("pause");
}

void view_registered_courses(int student_index){
    system("cls");
    cout<<"=================== My Registered Courses ===================\n";
    bool found = false;
    for(int i = 0; i < registration_count; i++){
        if(registrations[i].studentID == students[student_index].studentID){
            for(int j = 0; j < course_count; j++){
                if(course[j].course_code == registrations[i].course_code){
                    cout<<"Code: "<<course[j].course_code<<endl;
                    cout<<"Name: "<<course[j].course_name<<endl;
                    cout<<"Year: "<<course[j].year_offered<<endl;
                    cout<<"________________________________________________\n";
                    found = true;
                }
            }
        }
    }
    if(!found) cout<<"You are not registered for any courses.\n";
    system("pause");
}

void drop_course(int student_index){
    system("cls");
    cout<<"=================== Drop Course ===================\n";
    cout<<"Enter Course Code to drop: ";
    string course_code;
    getline(cin, course_code);

    int reg_index = -1;
    for(int i = 0; i < registration_count; i++){
        if(registrations[i].studentID == students[student_index].studentID &&
           registrations[i].course_code == course_code){
            reg_index = i;
            break;
        }
    }
    if(reg_index == -1){
        cout<<"You are not registered for "<<course_code<<".\n";
        system("pause");
        return;
    }

    cout<<"Are you sure you want to drop "<<course_code<<"?\n";
    cout<<"1. Confirm\n";
    cout<<"2. Cancel\n";
    int choice = validateInput(1, 2);
    if(choice == 2){
        cout<<"Drop cancelled.\n";
        system("pause");
        return;
    }

    for(int i = reg_index; i < registration_count - 1; i++){
        registrations[i] = registrations[i + 1];
    }
    registration_count--;
    cout<<"Successfully dropped "<<course_code<<".\n";
    save_registrations();
    system("pause");
}

void save_registrations(){
    ofstream outFile("registrations.txt");
    if(outFile.is_open()){
        for(int i = 0; i < registration_count; i++){
            outFile<<registrations[i].studentID<<"|"<<registrations[i].course_code<<"\n";
        }
        outFile.close();
    } else {
        cout<<"Error saving registrations!\n";
    }
}

void load_registrations(){
    ifstream inFile("registrations.txt");
    if(!inFile.is_open()) return;
    registration_count = 0;
    string line;
    while(getline(inFile, line) && registration_count < 500){
        if(line.empty()) continue;
        size_t pos = line.find('|');
        if(pos == string::npos) continue;
        try {
            registrations[registration_count].studentID = stoi(line.substr(0, pos));
            registrations[registration_count].course_code = line.substr(pos + 1);
            registration_count++;
        } catch(...){
            continue;
        }
    }
    inFile.close();
}
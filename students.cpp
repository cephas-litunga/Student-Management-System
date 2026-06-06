#include <iostream>
#include <limits>
#include "students.h"
#include <string>
using namespace std;

Student students[100];
int student_count = 0;
int next_student_id = 260000;

// Add a clear input buffer function to handle invalid inputs
void add_students(){
    cout<<"\n===== Adding New Student =====\n";
    cout<<"Enter Full Name: ";
    getline(cin, students[student_count].name);
    cout<<"Enter Age: ";
    cin>>students[student_count].age;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout<<"Enter Program: ";
    getline(cin, students[student_count].program);
    students[student_count].studentID = next_student_id++;
    student_count++;
    cout<<"Student added successfully!\n";
    cout<<"Student ID: "<<students[student_count - 1].studentID<<endl;
}

void view_all_students(){

    for(int i = 0; i < student_count; i++){
        cout<<"\nName: "<<students[i].name<<endl;
        cout<<"Age: "<<students[i].age<<endl;
        cout<<"Program: "<<students[i].program<<endl;
        cout<<"Student ID: "<<students[i].studentID<<endl;
        cout<<"_____________________________________\n\n";
    }
}

void search_students(){
    cout<<"\n===== Search Student =====\n";
    cout<<"Enter ID to search: ";
    int search_id;
    cin>>search_id;
    bool found = false;
    for(int i = 0; i < student_count; i++){
        if(students[i].studentID == search_id){
            cout<<"\nName: "<<students[i].name<<endl;
            cout<<"Age: "<<students[i].age<<endl;
            cout<<"Program: "<<students[i].program<<endl;
            cout<<"Student ID: "<<students[i].studentID<<endl;
            cout<<"_____________________________________\n\n";
            found = true;
        }
    }
    if(!found){
        cout<<"Student not found!\n";
    }
}

void edit_student_details(){
    if(student_count == 0){
        cout<<"No students found!\n";
        return;
    }
    cout<<"\n===== Edit Student Details =====\n";

    int search_id;
    bool found = false;
    cout<<"Enter student ID: ";
    cin>>search_id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    for(int i = 0; i < student_count; i++){
        if(search_id == students[i].studentID){
            cout<<"Enter Full Name: ";
            getline(cin, students[i].name);
            cout<<"Enter Age: ";
            cin>>students[i].age;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Enter Program: ";
            getline(cin, students[i].program);
            cout<<"Student Edited successfully!\n";
            found = true;
            break;
        }
    }
    if(!found){
        cout<<"Student not found\n";
    }
}

void delete_student(){
    if(student_count == 0){
        cout<<"No students found!\n";
        return;
    }
    cout<<"\n===== Delete Student =====\n";
    int search_id;
    bool found = false;
    cout<<"Enter student ID: ";
    cin>>search_id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    for(int i = 0; i < student_count; i++){
        if(search_id == students[i].studentID){
            for(int j = i; j < student_count - 1; j++){
                students[j] = students[j + 1];
            }
            student_count--;
            cout<<"Student deleted successfully!\n";
            found = true;
            break;
        }
    }
    if(!found){
        cout<<"Student not found\n";
    }
}


void edit_student_grades(){
    if(student_count == 0){
        cout<<"No students found!\n";
        return;
    }
    cout<<"\n===== Edit Student Grades =====\n";
    int search_id;
    cout<<"Enter student ID to edit grades: ";
    cin>>search_id;
    // cin.ignore(numeric_limits<streamsize>::max(), '\n');

    bool found = false;
    for(int i = 0; i < student_count; i++){
        if(search_id == students[i].studentID){
            found = true;
            cout<<"\n===== Entering Grades for "<<students[i].name<<" ====="<<endl;
            cout<<"Enter grades for 6 subjects (0-100):\n";
            string subjects[6] = {"MA110", "LA111", "PH110", "CS120", "CS130", "CS150"};
            
            for(int j = 0; j < 6; j++){
                cout<<subjects[j]<<" (0-100): ";
                while(!(cin>>students[i].grades[j]) || students[i].grades[j] < 0 || students[i].grades[j] > 100){
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout<<"Invalid input! Enter a grade between 0-100: ";
                }
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"\nGrades updated successfully!\n";
            break;
        }
    }
    
    if(!found){
        cout<<"Student not found!\n";
    }
}

void view_student_grades(){
    if(student_count == 0){
        cout<<"No students found!\n";
        return;
    }
    
    int search_id;
    cout<<"Enter student ID to view grades: ";
    cin>>search_id;
    // cin.ignore(numeric_limits<streamsize>::max(), '\n');

    bool found = false;
    for(int i = 0; i < student_count; i++){
        if(search_id == students[i].studentID){
            found = true;
            string subjects[6] = {"MA110", "LA111", "PH110", "CS120", "CS130", "CS150"};
            cout<<"\n===== Grades for "<<students[i].name<<" ====="<<endl;
            float total = 0;
            
            for(int j = 0; j < 6; j++){
                cout<<subjects[j]<<": "<<students[i].grades[j]<<endl;
                total += students[i].grades[j];
            }
            
            float average = total / 6;
            cout<<"\nTotal: "<<total<<endl;
            cout<<"Average: "<<average<<endl;
            cout<<"_____________________________________\n";
            break;
        }
    }
    
    if(!found){
        cout<<"Student not found!\n";
    }
}

#include "globals.h"
using namespace std;

Student students[100];
int student_count = 0;
int next_student_id = 260000;

void add_students(){
    system("cls");
    cout<<"===== Adding New Student =====\n";

    cout<<"Enter Full Name: ";
    getline(cin, students[student_count].name);

    cout<<"Enter Age: ";
    cin>>students[student_count].age;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout<<"Enter Gender: ";
    cin>>students[student_count].gender;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout<<"Enter Program: ";
    getline(cin, students[student_count].program);

    cout<<"Enter Email: ";
    getline(cin, students[student_count].email);

    cout<<"Enter Phone Number: ";
    cin>>students[student_count].phone_number;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout<<"Create Student Password: ";
    getline(cin, students[student_count].password);

    students[student_count].year_of_study = 1; // Default year of study for new students
    if(student_count == 0){
        next_student_id = 260001; // Start from 260001 if no students exist
    }
    students[student_count].studentID = next_student_id++;
    student_count++;

    cout<<"Student added successfully!\n";
    cout<<"Student ID: "<<students[student_count - 1].studentID<<endl;

    system("pause");
}

void view_all_students(){

    system("cls");
    if(student_count > 0){
        for(int i = 0; i < student_count; i++){
            cout<<"\nName: "<<students[i].name<<endl;
            cout<<"Age: "<<students[i].age<<endl;
            cout<<"Gender: "<<students[i].gender<<endl;
            cout<<"Program: "<<students[i].program<<endl;
            cout<<"Student ID: "<<students[i].studentID<<endl;
            cout<<"Email: "<<students[i].email<<endl;
            cout<<"Phone Number: "<<students[i].phone_number<<endl;
            cout<<"_____________________________________\n\n";
        }
    }else{
        cout<<"No students found!\n";
    }
    system("pause");

}

void search_students(){
    system("cls");
    cout<<"\n===== Search Student =====\n";
    cout<<"Enter ID to search: ";
    int search_id;
    cin>>search_id;
    bool found = false;
    for(int i = 0; i < student_count; i++){
        if(students[i].studentID == search_id){
            cout<<"\nName: "<<students[i].name<<endl;
            cout<<"Age: "<<students[i].age<<endl;
            cout<<"Gender: "<<students[i].gender<<endl;
            cout<<"Program: "<<students[i].program<<endl;
            cout<<"Student ID: "<<students[i].studentID<<endl;
            cout<<"Email: "<<students[i].email<<endl;
            cout<<"Phone Number: "<<students[i].phone_number<<endl;
            cout<<"_____________________________________\n\n";
            found = true;
        }
    }
    if(!found){
        cout<<"Student "<<search_id<<" not found!\n";
    }
    system("pause");
}

void edit_student_details(){
    system("cls");
    if(student_count == 0){
        cout<<"No students found!\n";
        system("pause");
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
            cout<<"Enter Email: ";
            getline(cin, students[i].email);
            cout<<"Enter Phone Number: ";
            cin>>students[i].phone_number;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Student Details updated successfully!\n";
            found = true;
            break;
        }
    }
    if(!found){
        cout<<"Student "<<search_id<<" not found\n";
    }
    system("pause");
}


void view_student_grades(){
    system("cls");
    if(student_count == 0){
        cout<<"No students found!\n";
        system("pause");
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
        cout<<"Student "<<search_id<<" not found!\n";
    }
    system("pause");
}

void edit_student_grades(){
    system("cls");
    if(student_count == 0){
        cout<<"No students found!\n";
        system("pause");
        return;
    }
    cout<<"\n===== Edit Student Grades =====\n";
    int search_id;
    cout<<"Enter student ID to edit grades: ";
    cin>>search_id;

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
        cout<<"Student "<<search_id<<" not found!\n";
    }
    system("pause");
}


void delete_student(){
    system("cls");
    string password;
    if(student_count == 0){
        cout<<"No students found!\n";
        system("pause");
        return;
    }
    cout<<"===== Delete Student =====\n";
    int search_id;
    bool found = false;
    cout<<"Enter student ID: ";
    cin>>search_id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout<<"Enter admin password to delete student: ";
    getline(cin, password);
    if (password != "admin123")
    {
        cout<<"Invalid password. Please try again: ";
        getline(cin, password);
    } else {
        cout<<"Password accepted. Proceeding with deletion...\n";
        sleep(1); // Optional: Add a small delay for better user experience
    }
    // cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
        cout<<"Student "<<search_id<<" not found\n";
    }
    system("pause");
}

void save_students(){
    ofstream outFile("students.txt");
    if(outFile.is_open()){
        for(int i = 0; i < student_count; i++){
            outFile<<students[i].studentID<<"|"<<students[i].password<<"|"
            <<students[i].name<<"|"<<students[i].age<<"|"<<students[i].program
            <<"|"<<students[i].email<<"|"<<students[i].phone_number<<"|"
            <<students[i].year_of_study<<"|" << students[i].gender;
            for(int j = 0; j < 6; j++){
                outFile<<"|"<<students[i].grades[j];
            }
            outFile<<"\n";
        }
        outFile.close();
    } else {
        cout<<"Error saving students!\n";
    }
}

void load_students(){
    ifstream inFile("students.txt");
    if(inFile.is_open()){
        student_count = 0;
        next_student_id = 260000;
        string id_str;
        while(getline(inFile, id_str, '|')){
            if(student_count >= 100) break;
            string password_str;
            if(!getline(inFile, password_str, '|')) break;
            if(!getline(inFile, students[student_count].name, '|')) break;
            string age_str;
            if(!getline(inFile, age_str, '|')) break;
            if(!getline(inFile, students[student_count].program, '|')) break;
            try {
                students[student_count].age = stoi(age_str);
                students[student_count].studentID = stoi(id_str);
            } catch(const std::exception&){
                // Skip malformed records instead of crashing.
                continue;
            }
            students[student_count].password = password_str;
            // Load the 6 grades
            for(int j = 0; j < 6; j++){
                string grade_str;
                if(j < 5){
                    if(!getline(inFile, grade_str, '|')) break;
                } else {
                    // Last grade - read until newline
                    if(!getline(inFile, grade_str)) break;
                }
                try {
                    students[student_count].grades[j] = stof(grade_str);
                } catch(const std::exception&){
                    students[student_count].grades[j] = 0.0f;
                }
            }
            
            if(students[student_count].studentID >= next_student_id){
                next_student_id = students[student_count].studentID + 1;
            }
            student_count++;
        }
        inFile.close();
    } else {
        cout<<"No saved students found!\n";
    }
}
#include "globals.h"
using namespace std;

Student students[100];
int student_count = 0;
int next_student_id = 260000;
Lecturer lecturer[100];
int lecturer_count = 0;


// Main Management functions
void student_management(){
    system("cls");
    while(1){
        int st_option = student_management_menu();
        switch(st_option){
            case 1: add_student(); break;
            case 2: search_student(); break;
            case 3: view_all_students(); break;
            case 4: edit_student_grades(); break;
            case 5: edit_student_details(); break;
            case 6: view_student_grades(); break;
            case 7: delete_student(); break;
            case 8: save_students(); save_courses(); return;
            default: cout<<"Invalid Option! Please try again.\n"; system("pause"); break;
        }
    }
}

void course_management(){
    system("cls");
    while(1){
        int option = course_management_menu();
        system("cls");
        switch(option){
            case 1: add_course(); break;
            case 2: view_all_courses(); break;
            case 3: delete_course(); break;
            case 4: search_course(); break;
            case 5: edit_course(); break;
            case 6: cout<<"Exiting!\n"; save_courses(); return; 
            default: cout<<"Invalid option! Please try again.\n"; system("pause");
        }
    }
}

void lecturer_management(){
    system("cls");
    while(1){
        int option = lecturer_management_menu();
        system("cls");
        switch(option){
            case 1: register_lecturer(); break;
            case 2: search_lecturer(); break;
            case 3: view_all_lecturers(); break;
            case 4: edit_lecturer(); break;
            case 5: delete_lecturer(); break;
            case 6: save_lecturers(); return; 
            default: cout<<"Invalid option! Please try again.\n"; system("pause");
        }
    }
}


// ------------------- Student Management Functions ------------------- 
void add_student(){
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
    cout<<"----------------- All Students -----------------\n";
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

void search_student(){
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
        cout<<"Invalid password. Please try again later\n";
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

// ----------------- Lecuterer Management Functions ----------------- 

void register_lecturer(){
    system("cls");
    cout<<"===== Registering New Lecturer =====\n";

    cout<<"Enter Full Name: ";
    getline(cin, lecturer[lecturer_count].name);

    cout<<"Enter Department: ";
    getline(cin, lecturer[lecturer_count].department);

    cout<<"Enter Email: ";
    getline(cin, lecturer[lecturer_count].email);

    cout<<"Enter Phone Number: ";
    cin>>lecturer[lecturer_count].phone_number;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout<<"Create Lecturer Password: ";
    getline(cin, lecturer[lecturer_count].password);

    lecturer[lecturer_count].lecturerID = 1000 + lecturer_count; // Assign a unique ID
    lecturer_count++;

    cout<<"Lecturer registered successfully!\n";
    cout<<"Lecturer ID: "<<lecturer[lecturer_count - 1].lecturerID<<endl;

    system("pause");
}

void search_lecturer(){
    system("cls");
    if(lecturer_count == 0){
        cout<<"No lecturers found!\n";
        system("pause");
        return;
    }
    cout<<"===== Search Lecturer =====\n";
    int search_id;
    bool found = false;
    cout<<"Enter lecturer ID: ";
    cin>>search_id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    for(int i = 0; i < lecturer_count; i++){
        if(search_id == lecturer[i].lecturerID){
            cout<<"Name: "<<lecturer[i].name<<endl;
            cout<<"Department: "<<lecturer[i].department<<endl;
            cout<<"Email: "<<lecturer[i].email<<endl;
            cout<<"Phone Number: "<<lecturer[i].phone_number<<endl;
            found = true;
            break;
        }
    }
    if(!found){
        cout<<"Lecturer with ID "<<search_id<<" not found!\n";
    }
    system("pause");
}

void view_all_lecturers(){
    system("cls");
    cout<<"----------------- All Lecturers -----------------\n";
    if(lecturer_count == 0){
        cout<<"No lecturers found!\n";
    } else {
        for(int i = 0; i < lecturer_count; i++){
            cout<<"Lecturer ID: "<<lecturer[i].lecturerID<<endl;
            cout<<"Name: "<<lecturer[i].name<<endl;
            cout<<"Department: "<<lecturer[i].department<<endl;
            cout<<"Email: "<<lecturer[i].email<<endl;
            cout<<"Phone Number: "<<lecturer[i].phone_number<<endl;
            cout<<"-----------------------------------\n";
        }
    }
    system("pause");
}

void edit_lecturer(){
    system("cls");
    if(lecturer_count == 0){
        cout<<"No lecturers found!\n";
        system("pause");
        return;
    }
    cout<<"===== Edit Lecturer Details =====\n";
    int search_id;
    bool found = false;
    cout<<"Enter lecturer ID: ";
    cin>>search_id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    for(int i = 0; i < lecturer_count; i++){
        if(search_id == lecturer[i].lecturerID){
            cout<<"Enter Full Name: ";
            getline(cin, lecturer[i].name);
            cout<<"Enter Department: ";
            getline(cin, lecturer[i].department);
            cout<<"Enter Email: ";
            getline(cin, lecturer[i].email);
            cout<<"Enter Phone Number: ";
            cin>>lecturer[i].phone_number;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Lecturer Details updated successfully!\n";
            found = true;
            break;
        }
    }
    if(!found){
        cout<<"Lecturer "<<search_id<<" not found\n";
    }
    system("pause");
}

void delete_lecturer(){
    system("cls");
    if(lecturer_count == 0){
        cout<<"No lecturers found!\n";
        system("pause");
        return;
    }
    cout<<"===== Delete Lecturer =====\n";
    int search_id;
    bool found = false;
    cout<<"Enter lecturer ID: ";
    cin>>search_id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    for(int i = 0; i < lecturer_count; i++){
        if(search_id == lecturer[i].lecturerID){
            for(int j = i; j < lecturer_count - 1; j++){
                lecturer[j] = lecturer[j + 1];
            }
            lecturer_count--;
            cout<<"Lecturer deleted successfully!\n";
            found = true;
            break;
        }
    }
    if(!found){
        cout<<"Lecturer "<<search_id<<" not found\n";
    }
    system("pause");
}

void save_lecturers(){
    ofstream outFile("lecturers.txt");
    if(outFile.is_open()){
        for(int i = 0; i < lecturer_count; i++){
            outFile<<lecturer[i].lecturerID<<"|"<<lecturer[i].name<<"|"
            <<lecturer[i].department<<"|"<<lecturer[i].email<<"|"
            <<lecturer[i].phone_number<<"|"<<lecturer[i].password<<"\n";
        }
        outFile.close();
    } else {
        cout<<"Error Saving Lecturers\n";
    }
}

void load_lecturers(){
    ifstream inFile("lecturers.txt");
    if(inFile.is_open()){
        lecturer_count = 0;
        string line;
        while(getline(inFile, line)){
            if(lecturer_count >= 100) break;
            size_t pos = 0;
            string token;
            int field_count = 0;
            while((pos = line.find('|')) != string::npos){
                token = line.substr(0, pos);
                switch(field_count){
                    case 0: lecturer[lecturer_count].lecturerID = stoi(token); break;
                    case 1: lecturer[lecturer_count].name = token; break;
                    case 2: lecturer[lecturer_count].department = token; break;
                    case 3: lecturer[lecturer_count].email = token; break;
                    case 4: lecturer[lecturer_count].phone_number = token; break;
                }
                line.erase(0, pos + 1);
                field_count++;
            }
            lecturer[lecturer_count].password = line; // Last field
            lecturer_count++;
        }
        inFile.close();
    } else {
        cout<<"No saved lecturers found!\n";
    }
}
#include "globals.h"

// ------------------- Student Management Functions ------------------- 

void add_student(){
    system("cls");
    cout<<"===== Adding New Student =====\n";

    students[student_count].name = validateString("Enter Full Name: ", 50, true);
    students[student_count].age = validateAge("Enter Age: ");
    students[student_count].gender = validateGender("Enter Gender: ");
    students[student_count].program = validateString("Enter Program: ", 50, true);
    students[student_count].email = validateEmail("Enter Email: ");
    students[student_count].phone_number = validatePhone("Enter Phone Number: ");
    students[student_count].password = validatePassword("Create Student Password: ");

    students[student_count].year_of_study = 1; // Default year of study for new students
    if(student_count == 0){
        next_student_id = 260001; // Start from 260001 if no students exist
    }
    students[student_count].studentID = next_student_id++;
    student_count++;

    cout<<"Student added successfully!\n";
    cout<<"Student ID: "<<students[student_count - 1].studentID<<endl;

    save_students();
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
    system("cls");
    for(int i = 0; i < student_count; i++){
        if(search_id == students[i].studentID){
            students[i].name = validateString("Enter Full Name: ", 50, true);
            students[i].age = validateAge("Enter Age: ");
            students[i].program = validateString("Enter Program: ", 50, true);
            students[i].email = validateEmail("Enter Email: ");
            students[i].phone_number = validatePhone("Enter Phone Number: ");
            cout<<"Student Details updated successfully!\n";
            found = true;
            break;
        }
    }

    save_students();
    
    if(!found){
        cout<<"Student "<<search_id<<" not found\n";
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

    save_students();

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
            outFile<<"\n";
        }
        outFile.close();
    } else {
        cout<<"Error saving students!\n";
    }
}

void load_students(){
    ifstream inFile("students.txt");
    if(!inFile.is_open()){
        cout<<"No saved students found!\n";
        return;
    }
    student_count = 0;
    next_student_id = 260000;
    string line;
    while(getline(inFile, line) && student_count < 100){
        if(line.empty()) continue;
        if(!line.empty() && line.back() == '\r') line.pop_back();

        size_t p[8];
        p[0] = line.find('|');
        for(int i = 1; i < 8; i++){
            p[i] = (p[i-1] == string::npos) ? string::npos : line.find('|', p[i-1] + 1);
        }
        if(p[7] == string::npos) continue;

        try {
            students[student_count].studentID     = stoi(line.substr(0, p[0]));
            students[student_count].password      = line.substr(p[0]+1, p[1]-p[0]-1);
            students[student_count].name          = line.substr(p[1]+1, p[2]-p[1]-1);
            students[student_count].age           = stoi(line.substr(p[2]+1, p[3]-p[2]-1));
            students[student_count].program       = line.substr(p[3]+1, p[4]-p[3]-1);
            students[student_count].email         = line.substr(p[4]+1, p[5]-p[4]-1);
            students[student_count].phone_number  = line.substr(p[5]+1, p[6]-p[5]-1);
            students[student_count].year_of_study = stoi(line.substr(p[6]+1, p[7]-p[6]-1));
            string gender_str = line.substr(p[7]+1);
            if(!gender_str.empty()) students[student_count].gender = gender_str[0];
            if(students[student_count].studentID >= next_student_id)
                next_student_id = students[student_count].studentID + 1;
            student_count++;
        } catch(...){
            continue;
        }
    }
    inFile.close();
}
#include "globals.h"

void add_student(){
    system("cls");

    if(student_count >= MAX_STUDENTS){
        cout<<"Student storage is full. Cannot add another student.\n";
        system("pause");
        return;
    }

    cout<<"===== Adding New Student =====\n";

    students[student_count].name = validateString("Enter Full Name: ", 50, true);
    students[student_count].age = validateAge("Enter Age: ");
    students[student_count].gender = validateGender("Enter Gender: ");
    students[student_count].program = validateString("Enter Program: ", 50, true);
    students[student_count].email = validateEmail("Enter Email: ");
    students[student_count].phone_number = validatePhone("Enter Phone Number: ");
    students[student_count].password = validatePassword("Create Student Password: ");
    students[student_count].year_of_study = 1;

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
    if(!(cin>>search_id)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"Invalid student ID.\n";
        system("pause");
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
            break;
        }
    }

    if(!found) cout<<"Student "<<search_id<<" not found!\n";
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
    cout<<"Enter student ID: ";
    if(!(cin>>search_id)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"Invalid student ID.\n";
        system("pause");
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for(int i = 0; i < student_count; i++){
        if(search_id == students[i].studentID){
            students[i].name = validateString("Enter Full Name: ", 50, true);
            students[i].age = validateAge("Enter Age: ");
            students[i].program = validateString("Enter Program: ", 50, true);
            students[i].email = validateEmail("Enter Email: ");
            students[i].phone_number = validatePhone("Enter Phone Number: ");

            cout<<"Student Details updated successfully!\n";
            save_students();
            system("pause");
            return;
        }
    }

    cout<<"Student "<<search_id<<" not found\n";
    system("pause");
}

void delete_student(){
    system("cls");

    if(student_count == 0){
        cout<<"No students found!\n";
        system("pause");
        return;
    }

    cout<<"===== Delete Student =====\n";

    int search_id;
    cout<<"Enter student ID: ";
    if(!(cin>>search_id)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"Invalid student ID.\n";
        system("pause");
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int student_index = -1;
    for(int i = 0; i < student_count; i++){
        if(students[i].studentID == search_id){
            student_index = i;
            break;
        }
    }

    if(student_index == -1){
        cout<<"Student "<<search_id<<" not found\n";
        system("pause");
        return;
    }

    cout<<"Delete "<<students[student_index].name<<" (ID "<<search_id<<")?\n";
    cout<<"1. Confirm\n";
    cout<<"2. Cancel\n";
    cout<<"Enter option: ";

    if(validateInput(1, 2) == 2){
        cout<<"Deletion cancelled.\n";
        system("pause");
        return;
    }

    // Remove the student.
    for(int i = student_index; i < student_count - 1; i++){
        students[i] = students[i + 1];
    }
    student_count--;

    // Remove all registrations belonging to the deleted student.
    int new_reg_count = 0;
    for(int j = 0; j < registration_count; j++){
        if(registrations[j].studentID != search_id){
            registrations[new_reg_count++] = registrations[j];
        }
    }
    registration_count = new_reg_count;

    // Remove all results belonging to the deleted student.
    int new_result_count = 0;
    for(int j = 0; j < result_count; j++){
        if(results[j].studentID != search_id){
            results[new_result_count++] = results[j];
        }
    }
    result_count = new_result_count;

    save_students();
    save_registrations();
    save_results();

    cout<<"Student and related registration/result records deleted successfully!\n";
    system("pause");
}

void save_students(){
    ofstream outFile("students.txt");

    if(!outFile.is_open()){
        cout<<"Error saving students!\n";
        return;
    }

    for(int i = 0; i < student_count; i++){
        outFile<<students[i].studentID<<"|"<<students[i].password<<"|"
               <<students[i].name<<"|"<<students[i].age<<"|"<<students[i].program
               <<"|"<<students[i].email<<"|"<<students[i].phone_number<<"|"
               <<students[i].year_of_study<<"|"<<students[i].gender<<"\n";
    }
}

void load_students(){
    ifstream inFile("students.txt");

    if(!inFile.is_open()){
        return;
    }

    student_count = 0;
    next_student_id = 260001;

    string line;

    while(getline(inFile, line) && student_count < MAX_STUDENTS){
        if(line.empty()) continue;
        if(line.back() == '\r') line.pop_back();

        size_t p[8];
        p[0] = line.find('|');

        for(int i = 1; i < 8; i++){
            p[i] = (p[i - 1] == string::npos)
                ? string::npos
                : line.find('|', p[i - 1] + 1);
        }

        if(p[7] == string::npos) continue;

        try{
            students[student_count].studentID =
                stoi(line.substr(0, p[0]));
            students[student_count].password =
                line.substr(p[0] + 1, p[1] - p[0] - 1);
            students[student_count].name =
                line.substr(p[1] + 1, p[2] - p[1] - 1);
            students[student_count].age =
                stoi(line.substr(p[2] + 1, p[3] - p[2] - 1));
            students[student_count].program =
                line.substr(p[3] + 1, p[4] - p[3] - 1);
            students[student_count].email =
                line.substr(p[4] + 1, p[5] - p[4] - 1);
            students[student_count].phone_number =
                line.substr(p[5] + 1, p[6] - p[5] - 1);
            students[student_count].year_of_study =
                stoi(line.substr(p[6] + 1, p[7] - p[6] - 1));

            string gender_str = line.substr(p[7] + 1);
            if(!gender_str.empty())
                students[student_count].gender = gender_str[0];

            if(students[student_count].studentID >= next_student_id)
                next_student_id = students[student_count].studentID + 1;

            student_count++;
        }
        catch(...){
            continue;
        }
    }
}

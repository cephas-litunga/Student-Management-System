#include "globals.h"
#include "database.h"

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

    if(!insert_student(students[student_count])){
        cout<<"Failed to add student to database.\n";
        system("pause");
        return;
    }

    next_student_id++;
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

            if(update_student(students[i])){
                cout<<"Student Details updated successfully in database!\n";
            }else{
                cout<<"Failed to update student details in database.\n";
            }

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

    if(!delete_student(search_id)){
        cout<<"Failed to delete student from database.\n";
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


    cout<<"Student and related registration/result records deleted successfully!\n";
    system("pause");
}

void load_students_from_database(){
    vector<Student> database_students = get_students();

    student_count = 0;
    next_student_id = 260001;

    for(const Student& student : database_students){
        if(student_count >= MAX_STUDENTS){
            break;
        }
        students[student_count] = student;

        if(student.studentID >= next_student_id){
            next_student_id = student.studentID + 1;
        }
        student_count++;
    }
}
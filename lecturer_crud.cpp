#include "globals.h"
#include "database.h"

int next_lecturer_id = 1000;

void register_lecturer(){
    system("cls");

    if(lecturer_count >= MAX_LECTURERS){
        cout<<"Lecturer storage is full. Cannot add another lecturer.\n";
        system("pause");
        return;
    }

    cout<<"===== Registering New Lecturer =====\n";

    lecturer[lecturer_count].name =
        validateString("Enter Full Name: ", 50, true);
    lecturer[lecturer_count].department =
        validateString("Enter Department: ", 50, true);
    lecturer[lecturer_count].email =
        validateEmail("Enter Email: ");
    lecturer[lecturer_count].phone_number =
        validatePhone("Enter Phone Number: ");
    lecturer[lecturer_count].password =
        validatePassword("Create Lecturer Password: ");

    lecturer[lecturer_count].lecturerID = next_lecturer_id++;

    if(!insert_lecturer(lecturer[lecturer_count])){
        cout<<"Failed to save lecturer to database.\n";
        system("pause");
        return;
    }

    next_lecturer_id++;
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
    cout<<"Enter lecturer ID: ";

    if(!(cin>>search_id)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"Invalid lecturer ID.\n";
        system("pause");
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for(int i = 0; i < lecturer_count; i++){
        if(search_id == lecturer[i].lecturerID){
            cout<<"Name: "<<lecturer[i].name<<endl;
            cout<<"Department: "<<lecturer[i].department<<endl;
            cout<<"Email: "<<lecturer[i].email<<endl;
            cout<<"Phone Number: "<<lecturer[i].phone_number<<endl;
            system("pause");
            return;
        }
    }

    cout<<"Lecturer with ID "<<search_id<<" not found!\n";
    system("pause");
}

void view_all_lecturers(){
    system("cls");
    cout<<"----------------- All Lecturers -----------------\n";

    if(lecturer_count == 0){
        cout<<"No lecturers found!\n";
    }else{
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
    cout<<"Enter lecturer ID: ";

    if(!(cin>>search_id)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"Invalid lecturer ID.\n";
        system("pause");
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for(int i = 0; i < lecturer_count; i++){
        if(search_id == lecturer[i].lecturerID){
            lecturer[i].name =
                validateString("Enter Full Name: ", 50, true);
            lecturer[i].department =
                validateString("Enter Department: ", 50, true);
            lecturer[i].email =
                validateEmail("Enter Email: ");
            lecturer[i].phone_number =
                validatePhone("Enter Phone Number: ");

            if(update_lecturer(lecturer[i])){
                cout<<"Lecturer changes saved to database.\n";
            }else{
                cout<<"Failed to save changes to database.\n";
            }

            system("pause");
            return;
        }
    }

    cout<<"Lecturer "<<search_id<<" not found\n";
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
    cout<<"Enter lecturer ID: ";

    if(!(cin>>search_id)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"Invalid lecturer ID.\n";
        system("pause");
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int lecturer_index = -1;

    for(int i = 0; i < lecturer_count; i++){
        if(search_id == lecturer[i].lecturerID){
            lecturer_index = i;
            break;
        }
    }

    if(lecturer_index == -1){
        cout<<"Lecturer "<<search_id<<" not found\n";
        system("pause");
        return;
    }

    cout<<"Delete "<<lecturer[lecturer_index].name
        <<" (ID "<<search_id<<")?\n";
    cout<<"1. Confirm\n";
    cout<<"2. Cancel\n";
    cout<<"Enter option: ";

    if(validateInput(1, 2) == 2){
        cout<<"Deletion cancelled.\n";
        system("pause");
        return;
    }

    if(!delete_lecturer(search_id)){
        cout<<"Failed to delete lecturer from database.\n";
        system("pause");
        return;
    }
    
    // Remove this lecturer from every course they were assigned to.
    for(int i = 0; i < course_count; i++){
        if(course[i].lecturerID == search_id){
            course[i].lecturerID = -1;
        }
    }

    for(int i = lecturer_index; i < lecturer_count - 1; i++){
        lecturer[i] = lecturer[i + 1];
    }
    lecturer_count--;

    cout<<"Lecturer deleted successfully. Related course assignments were removed.\n";
    system("pause");
}

void load_lecturers_from_database(){
    vector<Lecturer> database_lecturers = get_lecturers();

    lecturer_count = 0;
    next_lecturer_id = 1;

    for(const Lecturer& lecturer : database_lecturers){
        if(lecturer_count >= MAX_LECTURERS)
            break;
        
        ::lecturer[lecturer_count] = lecturer;

        if(lecturer.lecturerID >= next_lecturer_id)
            next_lecturer_id = lecturer.lecturerID + 1;

        lecturer_count++;
    }
}
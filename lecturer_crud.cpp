#include "globals.h"

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
    lecturer_count++;

    cout<<"Lecturer registered successfully!\n";
    cout<<"Lecturer ID: "<<lecturer[lecturer_count - 1].lecturerID<<endl;

    save_lecturers();
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

            cout<<"Lecturer Details updated successfully!\n";
            save_lecturers();
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

    save_lecturers();
    save_courses();

    cout<<"Lecturer deleted successfully. Related course assignments were removed.\n";
    system("pause");
}

void save_lecturers(){
    ofstream outFile("lecturers.txt");

    if(!outFile.is_open()){
        cout<<"Error Saving Lecturers\n";
        return;
    }

    for(int i = 0; i < lecturer_count; i++){
        outFile<<lecturer[i].lecturerID<<"|"
               <<lecturer[i].name<<"|"
               <<lecturer[i].department<<"|"
               <<lecturer[i].email<<"|"
               <<lecturer[i].phone_number<<"|"
               <<lecturer[i].password<<"\n";
    }
}

void load_lecturers(){
    ifstream inFile("lecturers.txt");

    if(!inFile.is_open())
        return;

    lecturer_count = 0;
    next_lecturer_id = 1000;

    string line;

    while(getline(inFile, line) && lecturer_count < MAX_LECTURERS){
        if(line.empty()) continue;
        if(line.back() == '\r') line.pop_back();

        size_t p1 = line.find('|');
        size_t p2 = (p1 == string::npos) ? string::npos : line.find('|', p1 + 1);
        size_t p3 = (p2 == string::npos) ? string::npos : line.find('|', p2 + 1);
        size_t p4 = (p3 == string::npos) ? string::npos : line.find('|', p3 + 1);
        size_t p5 = (p4 == string::npos) ? string::npos : line.find('|', p4 + 1);

        if(p5 == string::npos) continue;

        try{
            lecturer[lecturer_count].lecturerID =
                stoi(line.substr(0, p1));
            lecturer[lecturer_count].name =
                line.substr(p1 + 1, p2 - p1 - 1);
            lecturer[lecturer_count].department =
                line.substr(p2 + 1, p3 - p2 - 1);
            lecturer[lecturer_count].email =
                line.substr(p3 + 1, p4 - p3 - 1);
            lecturer[lecturer_count].phone_number =
                line.substr(p4 + 1, p5 - p4 - 1);
            lecturer[lecturer_count].password =
                line.substr(p5 + 1);

            if(lecturer[lecturer_count].lecturerID >= next_lecturer_id)
                next_lecturer_id = lecturer[lecturer_count].lecturerID + 1;

            lecturer_count++;
        }
        catch(...){
            continue;
        }
    }
}

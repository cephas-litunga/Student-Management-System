#include "globals.h"

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
    save_lecturers();
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
    save_lecturers();
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
        next_lecturer_id = 1000;
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
            lecturer[lecturer_count].password = line;
            if(lecturer[lecturer_count].lecturerID >= next_lecturer_id){
                next_lecturer_id = lecturer[lecturer_count].lecturerID + 1;
            }
            lecturer_count++;
        }
        inFile.close();
    } else {
        cout<<"No saved lecturers found!\n";
    }
}


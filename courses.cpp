#include "globals.h"

Course course[100];
int course_count = 0;

void add_course(){
    system("cls");
    cout<<"============== Adding New Course ============\n";
    cout<<"Enter Course Program: ";
    getline(cin, course[course_count].course_program);
    cout<<"Enter Course Name: ";
    getline(cin, course[course_count].course_name);
    cout<<"Enter Course Code: ";
    getline(cin, course[course_count].course_code);
    cout<<"Enter Course Year: ";
    cin>>course[course_count].year_offered;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    course_count++;
    cout<<"Course added successfully!\n";
    system("pause");
}

void view_all_courses(){
    system("cls");
    if (course_count > 0){
        for(int i = 0; i < course_count; i++){
            cout<<"Course Program: "<<course[i].course_program<<endl;
            cout<<"Course Name: "<<course[i].course_name<<endl;
            cout<<"Course Code: "<<course[i].course_code<<endl;
            cout<<"Year: "<<course[i].year_offered<<endl;
            cout<<"________________________________________________\n";
        }
    }
}

void search_course(){
    system("cls");
    string searched_course;
    cout<<"Enter Course Code: ";
    getline(cin, searched_course);
    bool found = false;
    for(int i = 0; i < course_count; i++){
        if(searched_course == course[i].course_code){
            cout<<"Course Program: "<<course[i].course_program<<endl;
            cout<<"Course Name: "<<course[i].course_name<<endl;
            cout<<"Course Code: "<<course[i].course_code<<endl;
            cout<<"Year: "<<course[i].year_offered<<endl;
            cout<<"________________________________________________\n";
            found = true;
        }
    }
    if(!found){
        cout<<"Course "<<searched_course<<" not found!\n";
    }

}

void edit_course(){
    if(course_count == 0){
        cout<<"No courses in system!\n";
        return;
    }
    string searched_course;
    bool found = false;
    cout<<"============= Edit Course Details =============\n";
    cout<<"Enter Course Code: ";
    getline(cin, searched_course);
    for(int i = 0; i < course_count; i++){
        if(searched_course == course[i].course_code){
            cout<<"Enter Course Program: ";
            getline(cin, course[i].course_program);
            cout<<"Enter Course Name: ";
            getline(cin, course[i].course_name);
            cout<<"Enter Course Code: ";
            getline(cin, course[i].course_code);
            cout<<"Enter Course Year: ";
            cin>>course[i].year_offered;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            found = true;
            cout<<"Course Edited Successfully\n";
        }
    }
    if(!found){
        cout<<"Course "<<searched_course<<" not found!\n";
    }

}

void delete_course(){
    system("cls");
    string password;
    if(course_count == 0){
        cout<<"No courses found!\n";
        system("pause");
        return;
    }
    cout<<"=================== Delete Course ===================\n";
    string search_id;
    bool found = false;
    cout<<"Enter Course Code: ";
    getline(cin, search_id);

    cout<<"Enter password to delete course: ";
    getline(cin, password);
    
    if(password != "admin123"){
        cout<<"Invalid password. Please try again later\n";
        return;
    }else{
        cout<<"Password accepted. Proceeding with deletion\n";
        sleep(1);
    }

    for(int i = 0; i < course_count; i++){
        if(search_id == course[i].course_code){
            for(int j = i; j < course_count - 1; j++){
                course[j] = course[j + 1];
            }
            course_count--;
            cout<<"Course deleted successfully\n";
            found = true;
            break;
        }
    }
    if(!found){
        cout<<"Course "<<search_id<<" not found\n";
    }
    system("pause");
}

void save_courses(){
    ofstream outFile("courses.txt");
    if(outFile.is_open()){
        for(int i = 0; i < course_count; i++){
            outFile<<course[i].course_code<<"|"<<course[i].course_name<<"|"
            <<course[i].course_program<<"|"<<course[i].year_offered;
            outFile<<"\n";
        }
        outFile.close();
    }else{
        cout<<"Error Saving Students\n";
    }
}

void load_courses(){
    ifstream inFile("courses.txt");
    if(!inFile.is_open()){
        return;
    }

    course_count = 0;
    string line;
    while(getline(inFile, line) && course_count < 100){
        if(line.empty()){
            continue;
        }

        size_t first = line.find('|');
        size_t second = (first == string::npos) ? string::npos : line.find('|', first + 1);
        size_t third = (second == string::npos) ? string::npos : line.find('|', second + 1);
        if(first == string::npos || second == string::npos || third == string::npos){
            continue;
        }

        course[course_count].course_code = line.substr(0, first);
        course[course_count].course_name = line.substr(first + 1, second - first - 1);
        course[course_count].course_program = line.substr(second + 1, third - second - 1);
        string yearText = line.substr(third + 1);
        try {
            course[course_count].year_offered = stoi(yearText);
        } catch(...){
            course[course_count].year_offered = 0;
        }

        course_count++;
    }

    inFile.close();
}

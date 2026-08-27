#include "globals.h"

// validate duplicate course helper function
static inline bool checkDuplicateCourse(const string& course_code, int exclude_index = -1){
    for(int i = 0; i< course_count; i++){
        if(i == exclude_index) continue;
        if(course[i].course_code == course_code) return true;
    }
    return false;
}

Course course[100];
int course_count = 0;

void add_course(){
    system("cls");
    cout<<"============== Adding New Course ============\n";
    course[course_count].course_program = validateString("Enter Course Program: ", 50, true);
    course[course_count].course_name = validateString("Enter Course Name: ", 50, true);
    course[course_count].course_code = validateString("Enter Course Code: ");
    course[course_count].year_offered = validateYear("Enter Course Year: ", 1, 4);
    course_count++;
    cout<<"Course added successfully!\n";
    save_courses();
    system("pause");
}

void view_all_courses(){
    system("cls");
    cout<<"=========================== Courses ===========================\n";
    if (course_count > 0){
        for(int i = 0; i < course_count; i++){
            cout<<"Course Program: "<<course[i].course_program<<endl;
            cout<<"Course Name: "<<course[i].course_name<<endl;
            cout<<"Course Code: "<<course[i].course_code<<endl;
            cout<<"Year: "<<course[i].year_offered<<endl;
            cout<<"___________________________________________________________\n";
        }
    }else{
        cout<<"No courses found!\n";
    }
    system("pause");
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
    system("pause");
}

void edit_course(){
    system("cls");
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
            course[i].course_program = validateString("Enter Course Program: ", 50, true);
            course[i].course_name = validateString("Enter Course Name: ", 50, true);
            course[i].course_code = validateString("Enter Course Code: ");
            course[i].year_offered = validateYear("Enter Course Year: ");
            found = true;
            cout<<"Course Edited Successfully\n";
        }
    }
    if(!found){
        cout<<"Course "<<searched_course<<" not found!\n";
    }
    save_courses();
    system("pause");
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
    save_courses();
    system("pause");
}

void save_courses(){
    ofstream outFile("courses.txt");
    if(outFile.is_open()){
        for(int i = 0; i < course_count; i++){
            outFile<<course[i].course_code<<"|"<<course[i].course_name<<"|"
            <<course[i].course_program<<"|"<<course[i].year_offered
            <<"|"<<course[i].lecturerID<<"|"<<course[i].has_assignement;
            outFile<<"\n";
        }
        outFile.close();
    }else{
        cout<<"Error Saving Courses\n";
    }
}

void load_courses(){
    ifstream inFile("courses.txt");
    if(!inFile.is_open()) return;

    course_count = 0;
    string line;
    while(getline(inFile, line) && course_count < 100){
        if(line.empty()) continue;

        size_t first  = line.find('|');
        size_t second = (first  == string::npos) ? string::npos : line.find('|', first  + 1);
        size_t third  = (second == string::npos) ? string::npos : line.find('|', second + 1);
        size_t fourth = (third  == string::npos) ? string::npos : line.find('|', third  + 1);
        size_t fifth = (fourth == string::npos) ? string::npos : line.find('|', fourth + 1);

        if(first == string::npos || second == string::npos || 
           third == string::npos || fourth == string::npos) continue;

        course[course_count].course_code    = line.substr(0, first);
        course[course_count].course_name    = line.substr(first  + 1, second - first  - 1);
        course[course_count].course_program = line.substr(second + 1, third  - second - 1);

        string yearText       = line.substr(third  + 1, fourth - third  - 1);
        string lecturerIDText = line.substr(fourth  + 1, fifth == string::npos ? string::npos : fifth - fourth - 1);
        string hasAssignmentText = (fifth == string::npos) ? "0" : line.substr(fifth + 1);

        try {
            course[course_count].year_offered = stoi(yearText);
            course[course_count].lecturerID   = stoi(lecturerIDText);
        } catch(...){
            course[course_count].year_offered = 0;
            course[course_count].lecturerID   = -1;
        }

        course_count++;
    }
    inFile.close();
}

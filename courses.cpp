#include "globals.h"

static bool checkDuplicateCourse(const string& course_code, int exclude_index = -1){
    for(int i = 0; i < course_count; i++){
        if(i == exclude_index) continue;
        if(course[i].course_code == course_code)
            return true;
    }
    return false;
}

Course course[MAX_COURSES];
int course_count = 0;

void add_course(){
    system("cls");

    if(course_count >= MAX_COURSES){
        cout<<"Course storage is full. Cannot add another course.\n";
        system("pause");
        return;
    }

    cout<<"============== Adding New Course ============\n";

    string code;
    while(true){
        code = validateString("Enter Course Code: ");
        if(checkDuplicateCourse(code)){
            cout<<"A course with code "<<code<<" already exists. Enter a different code.\n";
        }else{
            break;
        }
    }

    course[course_count].course_program =
        validateString("Enter Course Program: ", 50, true);
    course[course_count].course_name =
        validateString("Enter Course Name: ", 50, true);
    course[course_count].course_code = code;
    course[course_count].year_offered =
        validateYear("Enter Course Year: ", 1, 4);
    course[course_count].lecturerID = -1;
    course[course_count].has_assignement = false;

    course_count++;

    cout<<"Course added successfully!\n";
    save_courses();
    system("pause");
}

void view_all_courses(){
    system("cls");
    cout<<"=========================== Courses ===========================\n";

    if(course_count > 0){
        for(int i = 0; i < course_count; i++){
            cout<<"Course Program: "<<course[i].course_program<<endl;
            cout<<"Course Name: "<<course[i].course_name<<endl;
            cout<<"Course Code: "<<course[i].course_code<<endl;
            cout<<"Year: "<<course[i].year_offered<<endl;
            cout<<"Lecturer ID: "<<course[i].lecturerID<<endl;
            cout<<"Assignment: "<<(course[i].has_assignement ? "Enabled" : "Disabled")<<endl;
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

    for(int i = 0; i < course_count; i++){
        if(searched_course == course[i].course_code){
            cout<<"Course Program: "<<course[i].course_program<<endl;
            cout<<"Course Name: "<<course[i].course_name<<endl;
            cout<<"Course Code: "<<course[i].course_code<<endl;
            cout<<"Year: "<<course[i].year_offered<<endl;
            cout<<"________________________________________________\n";
            system("pause");
            return;
        }
    }

    cout<<"Course "<<searched_course<<" not found!\n";
    system("pause");
}

void edit_course(){
    system("cls");

    if(course_count == 0){
        cout<<"No courses in system!\n";
        system("pause");
        return;
    }

    string searched_course;
    cout<<"============= Edit Course Details =============\n";
    cout<<"Enter Course Code: ";
    getline(cin, searched_course);

    int course_index = -1;
    for(int i = 0; i < course_count; i++){
        if(searched_course == course[i].course_code){
            course_index = i;
            break;
        }
    }

    if(course_index == -1){
        cout<<"Course "<<searched_course<<" not found!\n";
        system("pause");
        return;
    }

    string new_program =
        validateString("Enter Course Program: ", 50, true);
    string new_name =
        validateString("Enter Course Name: ", 50, true);

    string new_code;
    while(true){
        new_code = validateString("Enter Course Code: ");

        if(checkDuplicateCourse(new_code, course_index)){
            cout<<"A course with code "<<new_code<<" already exists. Enter a different code.\n";
        }else{
            break;
        }
    }

    int new_year = validateYear("Enter Course Year: ", 1, 4);

    // If the code changes, update existing registrations/results so they
    // continue referring to the same course.
    if(new_code != course[course_index].course_code){
        for(int i = 0; i < registration_count; i++){
            if(registrations[i].course_code == course[course_index].course_code)
                registrations[i].course_code = new_code;
        }

        for(int i = 0; i < result_count; i++){
            if(results[i].course_code == course[course_index].course_code)
                results[i].course_code = new_code;
        }

        save_registrations();
        save_results();
    }

    course[course_index].course_program = new_program;
    course[course_index].course_name = new_name;
    course[course_index].course_code = new_code;
    course[course_index].year_offered = new_year;

    save_courses();

    cout<<"Course edited successfully.\n";
    system("pause");
}

void delete_course(){
    system("cls");

    if(course_count == 0){
        cout<<"No courses found!\n";
        system("pause");
        return;
    }

    cout<<"=================== Delete Course ===================\n";

    string search_code;
    cout<<"Enter Course Code: ";
    getline(cin, search_code);

    int course_index = -1;
    for(int i = 0; i < course_count; i++){
        if(search_code == course[i].course_code){
            course_index = i;
            break;
        }
    }

    if(course_index == -1){
        cout<<"Course "<<search_code<<" not found.\n";
        system("pause");
        return;
    }

    cout<<"Delete "<<course[course_index].course_code
        <<" - "<<course[course_index].course_name<<"?\n";
    cout<<"1. Confirm\n";
    cout<<"2. Cancel\n";
    cout<<"Enter option: ";

    if(validateInput(1, 2) == 2){
        cout<<"Deletion cancelled.\n";
        system("pause");
        return;
    }

    // Remove registrations for this course.
    int new_reg_count = 0;
    for(int i = 0; i < registration_count; i++){
        if(registrations[i].course_code != search_code)
            registrations[new_reg_count++] = registrations[i];
    }
    registration_count = new_reg_count;

    // Remove results for this course.
    int new_result_count = 0;
    for(int i = 0; i < result_count; i++){
        if(results[i].course_code != search_code)
            results[new_result_count++] = results[i];
    }
    result_count = new_result_count;

    // Remove the course itself.
    for(int i = course_index; i < course_count - 1; i++)
        course[i] = course[i + 1];

    course_count--;

    save_courses();
    save_registrations();
    save_results();

    cout<<"Course and related registration/result records deleted successfully.\n";
    system("pause");
}

void save_courses(){
    ofstream outFile("courses.txt");

    if(!outFile.is_open()){
        cout<<"Error Saving Courses\n";
        return;
    }

    for(int i = 0; i < course_count; i++){
        outFile<<course[i].course_code<<"|"
               <<course[i].course_name<<"|"
               <<course[i].course_program<<"|"
               <<course[i].year_offered<<"|"
               <<course[i].lecturerID<<"|"
               <<course[i].has_assignement<<"\n";
    }
}

void load_courses(){
    ifstream inFile("courses.txt");
    if(!inFile.is_open())
        return;

    course_count = 0;
    string line;

    while(getline(inFile, line) && course_count < MAX_COURSES){
        if(line.empty()) continue;
        if(line.back() == '\r') line.pop_back();

        size_t p1 = line.find('|');
        size_t p2 = (p1 == string::npos) ? string::npos : line.find('|', p1 + 1);
        size_t p3 = (p2 == string::npos) ? string::npos : line.find('|', p2 + 1);
        size_t p4 = (p3 == string::npos) ? string::npos : line.find('|', p3 + 1);
        size_t p5 = (p4 == string::npos) ? string::npos : line.find('|', p4 + 1);

        if(p5 == string::npos) continue;

        try{
            course[course_count].course_code =
                line.substr(0, p1);
            course[course_count].course_name =
                line.substr(p1 + 1, p2 - p1 - 1);
            course[course_count].course_program =
                line.substr(p2 + 1, p3 - p2 - 1);
            course[course_count].year_offered =
                stoi(line.substr(p3 + 1, p4 - p3 - 1));
            course[course_count].lecturerID =
                stoi(line.substr(p4 + 1, p5 - p4 - 1));
            course[course_count].has_assignement =
                stoi(line.substr(p5 + 1)) != 0;

            course_count++;
        }
        catch(...){
            continue;
        }
    }
}

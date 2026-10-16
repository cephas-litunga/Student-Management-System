#include "globals.h"
#include "database.h"

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
    course[course_count].has_assignment = false;

    if(!insert_course(course[course_count])){
        cout<<"Failed to insert course into database.\n";
        system("pause");
        return;
    }

    course_count++;

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
            cout<<"Assignment: "<<(course[i].has_assignment ? "Enabled" : "Disabled")<<endl;
            cout<<"______________________________________________________________\n";
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

    string new_program = validateString("Enter Course Program: ", 50, true);
    string new_name = validateString("Enter Course Name: ", 50, true);
    int new_year = validateYear("Enter Course Year: ", 1, 4);

    string old_course_code = course[course_index].course_code;

    course[course_index].course_program = new_program;
    course[course_index].course_name = new_name;
    course[course_index].year_offered = new_year;

    if(!update_course(course[course_index])){
        cout<<"Failed to update course in database.\n";
        system("pause");
        return;
    }
 
    cout<<"Course in database edited successfully.\n";
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

    // Delete course from database first.
    if(!delete_course(search_code)){
        cout<<"Failed to delete course from database.\n";
        system("pause");
        return;
    }

    // Remove course from memory.
    for(int i = course_index; i < course_count - 1; i++)
        course[i] = course[i + 1];

    course_count--;

    // Remove related registrations from memory.
    int new_reg_count = 0;

    for(int i = 0; i < registration_count; i++){
        if(registrations[i].course_code != search_code)
            registrations[new_reg_count++] = registrations[i];
    }

    registration_count = new_reg_count;

    // Remove related results from memory.
    int new_result_count = 0;

    for(int i = 0; i < result_count; i++){
        if(results[i].course_code != search_code)
            results[new_result_count++] = results[i];
    }

    result_count = new_result_count;  

    cout<<"Course and related registration/result records "
        <<"deleted successfully.\n";

    system("pause");
}

void load_courses_from_database(){
    vector<Course> database_courses = get_courses();

    course_count = 0;

    for(const Course& current_course : database_courses){
        if(course_count >= MAX_COURSES)
            break;
        course[course_count] = current_course;
        course_count++;
    }
}
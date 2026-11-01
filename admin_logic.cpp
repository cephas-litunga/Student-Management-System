#include "globals.h"
#include "database.h"

Student students[MAX_STUDENTS];
int student_count = 0;
int next_student_id = 260001;

Lecturer lecturer[MAX_LECTURERS];
int lecturer_count = 0;

void student_management(){
    system("cls");
    while(1){
        int st_option = student_management_menu();
        switch(st_option){
            case 1: add_student(); break;
            case 2: search_student(); break;
            case 3: view_all_students(); break;
            case 4: edit_student_details(); break;
            case 5: delete_student(); break;
            case 6: return;
            default: cout<<"Invalid Option! Please try again.\n"; system("pause"); break;
        }
    }
}

void course_management(){
    system("cls");
    while(1){
        int option = course_management_menu();
        system("cls");
        switch(option){
            case 1: add_course(); break;
            case 2: view_all_courses(); break;
            case 3: delete_course(); break;
            case 4: search_course(); break;
            case 5: edit_course(); break;
            case 6: cout<<"Exiting!\n"; return;
            default: cout<<"Invalid option! Please try again.\n"; system("pause");
        }
    }
}

void lecturer_management(){
    system("cls");
    while(1){
        int option = lecturer_management_menu();
        system("cls");
        switch(option){
            case 1: register_lecturer(); break;
            case 2: lecturer_assignment(); break;
            case 3: search_lecturer(); break;
            case 4: view_all_lecturers(); break;
            case 5: edit_lecturer(); break;
            case 6: delete_lecturer(); break;
            case 7: return;
            default: cout<<"Invalid option! Please try again.\n"; system("pause");
        }
    }
}

void lecturer_assignment(){
    system("cls");
    while(1){
        int option = lecturer_assignment_menu();
        system("cls");
        switch(option){
            case 1: assign_lecturer(); break;
            case 2: view_lecturer_courses(); break;
            case 3: view_course_lecturer(); break;
            case 4: remove_lecturer_assignment(); break;
            case 5: return;
            default: cout<<"Invalid option! Please try again.\n"; system("pause");
        }
    }
}

void academic_reports(){
    while(true){
        system("cls");

        cout << "========== Academic Reports ==========\n";
        cout << "1. Course Performance Report\n";
        cout << "2. Back\n";
        cout << "Enter option: ";

        
        int option;
        if(!(cin >> option)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input.\n";
            system("pause");
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if(option == 2){
            return;
        }

        if(option != 1){
            cout << "Invalid option.\n";
            system("pause");
            continue;
        }

        vector<Course> courses = get_courses();
        vector<Results> results = get_results();

        if(courses.empty()){
            cout << "\nNo courses found.\n";
            system("pause");
            continue;
        }

        cout << "\n========== Course Performance Report ==========\n";

        cout << left
             << setw(12) << "Code"
             << setw(30) << "Course"
             << right
             << setw(10) << "Completed"
             << setw(10) << "Passed"
             << setw(10) << "Failed"
             << setw(12) << "Pass Rate"
             << '\n';

        cout << string(94, '-') << '\n';

        for(const Course& course : courses){
            int completed = 0;
            int passed = 0;
            int failed = 0;

            for(const Results& result : results){
                if(result.course_code != course.course_code){
                    continue;
                }

                // Exclude results that are not yet complete.
                if(result.finalExam < 0 ||
                   result.finalMark < 0 ||
                   result.finalGrade.empty()){
                    continue;
                }

                completed++;

                if(result.finalMark >= 50){
                    passed++;
                }else{
                    failed++;
                }
            }

            double pass_rate = completed > 0
                ? (static_cast<double>(passed) / completed) * 100.0
                : 0.0;

            cout << left
                 << setw(12) << course.course_code
                 << setw(30) << course.course_name
                 << right
                 << setw(10) << completed
                 << setw(10) << passed
                 << setw(10) << failed;

            if(completed > 0){
                cout << setw(11) << fixed << setprecision(1)
                     << pass_rate << "%";
            }else{
                cout << setw(11) << "N/A";
            }

            cout << '\n';
        }

        cout << "\nPass mark: 50% or above.\n";
        system("pause");
    }
}

void toggle_results_publishing(){
    system("cls");

    cout<<"========== Result Publication Control ==========\n";

    bool currently_published = get_results_published();

    cout<<"Current status: "
        << (currently_published ? "Published" : "Not Published") << "\n";
    cout<<"------------------------------------------------\n";

    if(currently_published){
        cout<<"1. Unpublish Results\n";
    }else{
        cout<<"1. Publish Results\n";
    }

    cout<<"2. Cancel\n";
    cout<<"Enter option: ";
    if(validateInput(1, 2) == 2){
        cout<<"Operation cancelled.\n";
        system("pause");
        return;
    }

    bool new_state = !currently_published;

    if(!set_results_published(new_state)){
        cout<<"Failed to update result publication status in database.\n";
        system("pause");
        return;
    } 

    cout<<"Results are now "
        << (new_state ? "Published" : "Not Published") << ".\n";

    if(!new_state){
        cout << "Students will not be able to view final results "
             << "until they are published again.\n";
    }

    system("pause");
}
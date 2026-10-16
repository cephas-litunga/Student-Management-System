#include "globals.h"
#include "database.h"

Results results[MAX_RESULTS];
int result_count = 0;

string assign_grade(float final_mark){
    if(final_mark >= 86) return "A+";
    if(final_mark >= 76) return "A";
    if(final_mark >= 68) return "B+";
    if(final_mark >= 62) return "B";
    if(final_mark >= 56) return "C+";
    if(final_mark >= 50) return "C";
    if(final_mark >= 40) return "D+";
    return "D";
}

float calculate_test_CA(float score, float total, bool has_assignment){
    float weight = has_assignment ? 15.0f : 20.0f;
    return (score / total) * weight;
}

float calculate_assignment_CA(float score){
    return (score / 100.0f) * 10.0f;
}

void enter_ca_marks(int lecturer_index, int course_index){
    (void)lecturer_index;

    system("cls");
    cout<<"=================== Enter CA Marks ==================\n";
    cout<<"Course: "<<course[course_index].course_code
        <<" - "<<course[course_index].course_name<<"\n";
    cout<<"Has Assignment: "
        <<(course[course_index].has_assignment ? "Yes" : "No")<<"\n";
    cout<<"_____________________________________________________\n";

    int student_id;
    cout<<"Enter Student ID: ";

    if(!(cin>>student_id)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"Invalid student ID.\n";
        system("pause");
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int student_index = -1;
    for(int i = 0; i < student_count; i++){
        if(students[i].studentID == student_id){
            student_index = i;
            break;
        }
    }

    if(student_index == -1){
        cout<<"Student "<<student_id<<" not found!\n";
        system("pause");
        return;
    }

    bool registered = false;
    for(int i = 0; i < registration_count; i++){
        if(registrations[i].studentID == student_id &&
           registrations[i].course_code == course[course_index].course_code){
            registered = true;
            break;
        }
    }

    if(!registered){
        cout<<"Student "<<students[student_index].name
            <<" is not registered for "
            <<course[course_index].course_code<<".\n";
        system("pause");
        return;
    }

    // Reuse an existing result record if one exists.
    // This prevents duplicate results for the same student/course.
    int result_index = -1;
    for(int i = 0; i < result_count; i++){
        if(results[i].studentID == student_id &&
           results[i].course_code == course[course_index].course_code){
            result_index = i;
            break;
        }
    }

    bool created_new_result = false;

    if(result_index == -1){
        if(result_count >= MAX_RESULTS){
            cout<<"Result storage is full. Cannot save another result.\n";
            system("pause");
            return;
        }

        result_index = result_count++;
        created_new_result = true;
        results[result_index] = Results();
        results[result_index].studentID = student_id;
        results[result_index].course_code = course[course_index].course_code;
    }

    Results previous_result = results[result_index];
    // Preserve an already-entered final examination if CA is being edited.
    float previous_final_exam = results[result_index].finalExam;

    system("cls");
    cout<<"================== Enter CA Marks ==================\n\n";
    cout<<"Entering CA marks for "<<students[student_index].name<<"...\n";
    cout<<"____________________________________________________\n";

    float test1_total;
    float test1_score;

    cout<<"Test 1\n";
    test1_total = validateScore("Enter Test 1 Total: ", 1, 100);
    test1_score = validateScore("Enter Test 1 Score: ", 0, test1_total);

    float test1_ca = calculate_test_CA(
        test1_score,
        test1_total,
        course[course_index].has_assignment
    );

    float test2_total;
    float test2_score;

    cout<<"Test 2\n";
    test2_total = validateScore("Enter Test 2 Total: ", 1, 100);
    test2_score = validateScore("Enter Test 2 Score: ", 0, test2_total);

    float test2_ca = calculate_test_CA(
        test2_score,
        test2_total,
        course[course_index].has_assignment
    );

    float assignment_ca = 0.0f;

    if(course[course_index].has_assignment){
        float assignment_score;

        cout<<"Assignment\n";
        assignment_score =
            validateScore("Enter Assignment Score (out of 100): ", 0, 100);

        assignment_ca = calculate_assignment_CA(assignment_score);
    }

    results[result_index].test1 = test1_ca;
    results[result_index].test2 = test2_ca;
    results[result_index].assignment = assignment_ca;
    results[result_index].continuousAssessment =
        test1_ca + test2_ca + assignment_ca;

    // Keep final exam/final result if it already exists.
    results[result_index].finalExam = previous_final_exam;

    if(previous_final_exam >= 0.0f){
        results[result_index].finalMark =
            results[result_index].continuousAssessment + previous_final_exam;
        results[result_index].finalGrade =
            assign_grade(results[result_index].finalMark);
    }else{
        results[result_index].finalMark = -1.0f;
        results[result_index].finalGrade = "";
    }

    cout<<"___________________________________________________\n";
    cout<<"CA: "<<results[result_index].continuousAssessment<<"/40\n";

    if(previous_final_exam >= 0.0f){
        cout<<"Final Exam: "<<results[result_index].finalExam<<"/60\n";
        cout<<"Final Mark: "<<results[result_index].finalMark<<"/100\n";
        cout<<"Grade: "<<results[result_index].finalGrade<<"\n";
    }

    if(!save_result(results[result_index])){
        if(created_new_result){
            result_count--;
        }else{
            results[result_index] = previous_result;
        }

        cout << "Failed to save CA marks to the database.\n";
        system("pause");
        return;
    }

    cout << "CA marks saved successfully!\n";   
    system("pause");
}

void enter_final_exam(int lecturer_index, int course_index){
    (void)lecturer_index;

    system("cls");
    cout<<"=================== Enter Final Exam Marks ==================\n";
    cout<<"Course: "<<course[course_index].course_code
        <<" - "<<course[course_index].course_name<<"\n";
    cout<<"___________________________________________________\n";

    int student_id;
    cout<<"Enter Student ID: ";

    if(!(cin>>student_id)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"Invalid student ID.\n";
        system("pause");
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int result_index = -1;

    for(int i = 0; i < result_count; i++){
        if(results[i].studentID == student_id &&
           results[i].course_code == course[course_index].course_code){
            result_index = i;
            break;
        }
    }

    if(result_index == -1){
        cout<<"No CA record found for this student in "
            <<course[course_index].course_code<<".\n";
        cout<<"Please enter CA marks first.\n";
        system("pause");
        return;
    }

    string student_name;
    bool student_exists = false;

    for(int i = 0; i < student_count; i++){
        if(students[i].studentID == student_id){
            student_name = students[i].name;
            student_exists = true;
            break;
        }
    }

    if(!student_exists){
        cout<<"Student no longer exists in the system.\n";
        system("pause");
        return;
    }

    cout<<"Student: "<<student_name<<endl;
    cout<<"__________________________________________\n";
    cout<<"CA: "<<results[result_index].continuousAssessment<<"/40\n";

    float exam_score =
        validateScore("Enter Final Exam Score (out of 100): ", 0, 100);

    Results previous_result = results[result_index];

    results[result_index].finalExam = (exam_score / 100.0f) * 60.0f;
    results[result_index].finalMark =
        results[result_index].continuousAssessment +
        results[result_index].finalExam;
    results[result_index].finalGrade =
        assign_grade(results[result_index].finalMark);

    cout<<"__________________________________________\n";
    cout<<"CA: "<<results[result_index].continuousAssessment<<"/40\n";
    cout<<"Final Exam: "<<results[result_index].finalExam<<"/60\n";
    cout<<"Final Mark: "<<results[result_index].finalMark<<"/100\n";
    cout<<"Grade: "<<results[result_index].finalGrade<<"\n";

    if(!save_result(results[result_index])){
        results[result_index] = previous_result;

        cout << "Failed to save results to the database.\n";
        system("pause");
        return;
    }

    cout << "Results saved successfully!\n";
    system("pause");
}

void load_results_from_database()
{
    vector<Results> loaded_results = get_results();

    if(loaded_results.size() > MAX_RESULTS){
        cerr << "Database contains more results than "
             << "the application can hold.\n";
        return;
    }

    result_count = 0;

    for(const Results& result : loaded_results){
        results[result_count++] = result;
    }
}
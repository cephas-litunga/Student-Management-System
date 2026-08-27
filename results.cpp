#include "globals.h"
using namespace std;
Results results[500];
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
    float weight = has_assignment ? 15.0 : 20.0;
    return (score / total) * weight;
}

float calculate_assignment_CA(float score){
    return (score / 100.0) * 10.0;
}

void enter_ca_marks(int lecturer_index, int course_index){
    system("cls");
    cout<<"=================== Enter CA Marks ==================\n";
    cout<<"Course: "<<course[course_index].course_code<<" - "<<course[course_index].course_name<<"\n";
    cout<<"Has Assignment: "<<(course[course_index].has_assignement ? "Yes" : "No")<<"\n";
    cout<<"_____________________________________________________\n";

    // Search student by ID
    int student_id;
    cout<<"Enter Student ID: ";
    cin>>student_id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Verify student exists
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

    // verify registered
    bool registered = false;
    for(int i = 0; i < registration_count; i++){
        if(registrations[i].studentID == student_id && registrations[i].course_code == course[course_index].course_code){
            registered = true;
            break;
        }
    }
    if(!registered){
        cout<<"Student "<<students[student_index].name<<" is not registered for "<<course[course_index].course_code<<".\n";
        system("pause");
        return;
    }

    system("cls");
    cout<<"================== Enter CA Marks ==================\n\n";
    cout<<"Entering CA marks for "<<students[student_index].name<<"...\n";
    cout<<"____________________________________________________\n";

    Results r;
    r.studentID = student_id;
    r.course_code = course[course_index].course_code;
    r.finalExam = -1;
    r.finalMark = -1;
    r.finalGrade = "";
    
    //Test 1
    float test1_score, test1_total;
    cout<<"Test 1\n";
    test1_total = validateScore("Enter Test 1 Total: ", 1, 100);
    cout<<"Enter Test 1 Score: ";
    test1_score = validateScore("", 0, test1_total);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    r.test1 = calculate_test_CA(test1_score, test1_total, course[course_index].has_assignement);
    
    // Test 2
    float test2_score, test2_total;
    cout<<"Test 2\n";
    test2_total = validateScore("Enter Test 2 Total: ", 1, 100);
    cout<<"Enter Test 2 Score: ";
    test2_score = validateScore("", 0, test2_total);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    r.test2 = calculate_test_CA(test2_score, test2_total, course[course_index].has_assignement);

    // Assignment
    r.assignment = 0;
    if(course[course_index].has_assignement){
        float assignment_score;
        cout<<"Assignment\n";
        cout<<"Enter Assignment Score (out of 100): ";
        assignment_score = validateScore("", 0, 100);
        r.assignment = calculate_assignment_CA(assignment_score);
    }

    // calculate CA
    r.continousAssessment = r.test1 + r.test2 + r.assignment;
    cout<<"___________________________________________________\n";
    cout<<"CA: "<<r.continousAssessment<<"/40\n";

    results[result_count] = r;
    result_count++;
    save_results();
    cout<<"CA marks saved successfully!\n";
    system("pause");
}

void enter_final_exam(int leterer_index, int course_index){
    system("cls");
    cout<<"=================== Enter Final Exam Marks ==================\n";
    cout<<"Course: "<<course[course_index].course_code<<" - "<<course[course_index].course_name<<"\n";
    cout<<"___________________________________________________\n";

    // search student by ID
    int student_id;
    cout<<"Enter Student ID: ";
    cin>>student_id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Find existing result
    int result_index = -1;
    for(int i = 0; i < result_count; i++){
        if(results[i].studentID == student_id && results[i].course_code == course[course_index].course_code){
            result_index = i;
            break;
        }
    }
    if(result_index == -1){
        cout<<"No CA record found for this student in "<<course[course_index].course_code<<".\n";
        cout<<"Please enter CA marks first.\n";
        system("pause");
        return;
    }

    // Verify student exists
    string student_name = " ";
    for(int i = 0; i < student_count; i++){
        if(students[i].studentID == student_id){
            student_name = students[i].name;
            break;
        }
    }

    // Show CA first
    cout<<"Student: "<<student_name<<endl;
    cout<<"__________________________________________\n";
    cout<<"CA: "<<results[result_index].continousAssessment<<"/40\n";

    // Enter Final Exam
    float exam_score;
    exam_score = validateScore("Enter Final Exam Score(out of 100): ", 0, 100);

    results[result_index].finalExam = (exam_score/100.0) * 60;
    results[result_index].finalMark = results[result_index].continousAssessment + results[result_index].finalExam;
    results[result_index].finalGrade = assign_grade(results[result_index].finalMark);
    cout<<"__________________________________________\n";
    cout<<"CA: "<<results[result_index].continousAssessment<<"/40\n";
    cout<<"Final Exam: "<<results[result_index].finalExam<<"/60\n";
    cout<<"Final Mark: "<<results[result_index].finalMark<<"/100\n";
    cout<<"Grade: "<<results[result_index].finalGrade<<"\n";

    save_results();
    cout<<"Results saved successfully!\n";
    system("pause");

}


void save_results(){
    ofstream outFile("results.txt");
    if(outFile.is_open()){
        for(int i = 0; i < result_count; i++){
            outFile<<results[i].studentID<<"|"<<results[i].course_code<<"|"<<results[i].test1<<"|"
            <<results[i].test2<<"|"<<results[i].assignment<<"|"<<results[i].continousAssessment<<
            "|"<<results[i].finalExam<<"|"<<results[i].finalMark<<"|"<<results[i].finalGrade<<"\n";
        }
        outFile.close();
    }else{
        cout<<"Error saving results.\n";
    }
}

void load_results(){
    ifstream inFile("results.txt");
    if(!inFile.is_open()) return;
    result_count = 0;
    string line;
    while(getline(inFile, line) && result_count < 500){
        if(line.empty()) continue;
        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);
        size_t p3 = line.find('|', p2 + 1);
        size_t p4 = line.find('|', p3 + 1);
        size_t p5 = line.find('|', p4 + 1);
        size_t p6 = line.find('|', p5 + 1);
        size_t p7 = line.find('|', p6 + 1);
        size_t p8 = line.find('|', p7 + 1);

        if(p6 == string::npos) continue;
        try{
            results[result_count].studentID = stoi(line.substr(0,p1));
            results[result_count].course_code = line.substr(p1+1, p2-p1-1);
            results[result_count].test1 = stof(line.substr(p2+1, p3-p2-1));
            results[result_count].test2 = stof(line.substr(p3+1, p4-p3-1));
            results[result_count].assignment = stof(line.substr(p4+1, p5-p4-1));
            results[result_count].continousAssessment = stof(line.substr(p5+1, p6-p5-1));
            results[result_count].finalExam = stof(line.substr(p6+1, p7-p6-1));
            results[result_count].finalMark = stof(line.substr(p7+1, p8-p7-1));
            results[result_count].finalGrade = (p8 != string::npos) ? line.substr(p8+1) :  "";
            result_count++;
        } catch(...){
            continue;
        }
    }
    inFile.close();
}
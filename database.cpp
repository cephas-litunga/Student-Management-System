#include <iostream>
#include "database.h"

using namespace std;

static sqlite3* db = nullptr;

bool initialize_database(){
    int result_code = sqlite3_open("sms.db", &db);
    char* error_message =  nullptr;

    if(result_code != SQLITE_OK){
        cerr<<"Failed to open database: "<<sqlite3_errmsg(db)<<endl;
        return false;
    }

    cout<<"Connected to database successfully\n";

    result_code = sqlite3_exec(db, "PRAGMA foreign_keys = ON;", nullptr, nullptr, &error_message);
    if(result_code != SQLITE_OK){
        cerr<<"Failed to enable foreign keys."<<endl;
        return false;
    }

    const char* sql = R"(
        CREATE TABLE IF NOT EXISTS students(
            student_id INTEGER PRIMARY KEY,
            name TEXT NOT NULL,
            program TEXT NOT NULL,
            email TEXT NOT NULL,
            password TEXT NOT NULL,
            phone_number TEXT,
            age INTEGER,
            year_of_study INTEGER,
            gender TEXT
        );
    )";

    result_code = sqlite3_exec(db, sql, nullptr, nullptr, &error_message);
    if(result_code != SQLITE_OK)
    {
        cerr<<"Failed to create students table: "<<error_message<<endl;
        sqlite3_free(error_message);
        return false;
    }

    cout<<"students table ready.\n";

    const char* lecturerSQL = R"(
        CREATE TABLE IF NOT EXISTS lecturers(
            lecturer_id INTEGER PRIMARY KEY,
            name TEXT NOT NULL,
            email TEXT NOT NULL,
            password TEXT NOT NULL,
            phone_number TEXT NOT NULL,
            department TEXT
        );
    )";

    result_code = sqlite3_exec(db, lecturerSQL, nullptr, nullptr, &error_message);
    if(result_code != SQLITE_OK){
        cerr<<"Failed to create lecturers table: "<<error_message<<endl;
        sqlite3_free(error_message);
        return false;
    }

    cout<<"Lecturers table ready\n";

    const char* courseSQL = R"(
        CREATE TABLE IF NOT EXISTS courses(
            course_code TEXT PRIMARY KEY,
            course_name TEXT NOT NULL,
            course_program TEXT NOT NULL, 
            year_offered INTEGER NOT NULL,
            lecturer_id INTEGER,
            has_assignment INTEGER NOT NULL DEFAULT 0,
            FOREIGN KEY(lecturer_id) REFERENCES lecturers(lecturer_id)
        );
    )";

    result_code = sqlite3_exec(db, courseSQL, nullptr, nullptr, &error_message);
    if(result_code != SQLITE_OK){
        cerr<<"Failed to create courses table: "<<error_message<<endl;
        sqlite3_free(error_message);
        return false;
    }

    cout<<"Courses table ready."<<endl;

    const char* registrationSQL = R"(
        CREATE TABLE IF NOT EXISTS registrations(
            student_id INTEGER NOT NULL,
            course_code TEXT NOT NULL,

            PRIMARY KEY (student_id, course_code),

            FOREIGN KEY (student_id)
                REFERENCES students(student_id),

            FOREIGN KEY (course_code)
                REFERENCES courses(course_code)
        );
    )";

    result_code = sqlite3_exec(db, registrationSQL, nullptr, nullptr, &error_message);
    if(result_code != SQLITE_OK){
        cerr<<"Failed to create registrations table: "<<error_message<<endl;
        sqlite3_free(error_message);
        return false;
    }

    cout<<"Registrations table ready."<<endl;
    //-----------------
    // const char* dropResultsSQL = R"(
    //     DROP TABLE IF EXISTS results;
    // )";

    // result_code = sqlite3_exec(db, dropResultsSQL, nullptr, nullptr, &error_message);
    // if(result_code != SQLITE_OK){
    //     cerr<<"Failed to drop results table: "<<error_message<<endl;
    //     sqlite3_free(error_message);
    //     return false;
    // }
    //-----------------
    const char* resultsSQL = R"(
        CREATE TABLE IF NOT EXISTS results(
            student_id INTEGER NOT NULL,
            course_code TEXT NOT NULL,

            test1 REAL NOT NULL,
            test2 REAL NOT NULL,
            assignment REAL NOT NULL,
            continuous_assessment REAL NOT NULL,

            final_exam REAL,
            final_mark REAL,
            final_grade TEXT,

            PRIMARY KEY (student_id, course_code),

            FOREIGN KEY (student_id)
                REFERENCES students(student_id),

            FOREIGN KEY (course_code)
                REFERENCES courses(course_code),

            FOREIGN KEY (student_id, course_code)
                REFERENCES registrations(student_id, course_code)
        );
    )";

    result_code = sqlite3_exec(db, resultsSQL, nullptr, nullptr, &error_message);
    if(result_code != SQLITE_OK){
        cerr<<"Failed to create results table: "<<error_message<<endl;
        sqlite3_free(error_message);
        return false;
    }

    cout<<"Results table ready.\n";

    return true;
}

void close_database(){
    if(db != nullptr){
        sqlite3_close(db);
        db = nullptr;
    }
}

bool insert_student(const Student& student){
    const char* sql = R"(
        INSERT INTO students
        (student_id, name, program, email, password,
         phone_number, age, year_of_study, gender)
        VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?);
    )";

    sqlite3_stmt* statement = nullptr;

    int resultCode = sqlite3_prepare_v2( db, sql, -1, &statement, nullptr);

    if(resultCode != SQLITE_OK){
        cerr << "Failed to prepare student insertion." << endl;
        cerr << "SQLite error code: " << resultCode << endl;
        cerr << "SQLite error: " << sqlite3_errmsg(db) << endl;

        return false;
    }

    sqlite3_bind_int(statement, 1, student.studentID);
    sqlite3_bind_text(statement, 2, student.name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 3, student.program.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 4, student.email.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 5, student.password.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 6, student.phone_number.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(statement, 7, student.age);
    sqlite3_bind_int(statement, 8, student.year_of_study);

    string gender(1, student.gender);

    sqlite3_bind_text(
        statement,
        9,
        gender.c_str(),
        -1,
        SQLITE_TRANSIENT
    );

    resultCode = sqlite3_step(statement);

    if(resultCode != SQLITE_DONE)
    {
        cerr << "Failed to insert student." << endl;
        cerr << "SQLite error: " << sqlite3_errmsg(db) << endl;

        sqlite3_finalize(statement);
        return false;
    }

    sqlite3_finalize(statement);

    cout << "Student inserted successfully." << endl;

    return true;
}

bool insert_lecturer(const Lecturer& lecturer){
    const char* sql = R"(
        INSERT INTO lecturers
        (lecturer_id, name, email, password, phone_number, department)
        VALUES (?, ?, ?, ?, ?, ?);
    )";

    sqlite3_stmt* statement = nullptr;

    int resultCode = sqlite3_prepare_v2(
        db,
        sql,
        -1,
        &statement,
        nullptr
    );

    if(resultCode != SQLITE_OK)
    {
        cerr << "Failed to prepare lecturer insertion." << endl;
        cerr << "SQLite error: "
             << sqlite3_errmsg(db) << endl;

        return false;
    }

    sqlite3_bind_int(
        statement,
        1,
        lecturer.lecturerID
    );

    sqlite3_bind_text(
        statement,
        2,
        lecturer.name.c_str(),
        -1,
        SQLITE_TRANSIENT
    );

    sqlite3_bind_text(
        statement,
        3,
        lecturer.email.c_str(),
        -1,
        SQLITE_TRANSIENT
    );

    sqlite3_bind_text(
        statement,
        4,
        lecturer.password.c_str(),
        -1,
        SQLITE_TRANSIENT
    );

    sqlite3_bind_text(
        statement,
        5,
        lecturer.phone_number.c_str(),
        -1,
        SQLITE_TRANSIENT
    );

    sqlite3_bind_text(
        statement,
        6,
        lecturer.department.c_str(),
        -1,
        SQLITE_TRANSIENT
    );

    resultCode = sqlite3_step(statement);

    if(resultCode != SQLITE_DONE)
    {
        cerr << "Failed to insert lecturer." << endl;
        cerr << "SQLite error: "
             << sqlite3_errmsg(db) << endl;

        sqlite3_finalize(statement);
        return false;
    }

    sqlite3_finalize(statement);

    cout << "Lecturer inserted successfully." << endl;

    return true;
}

bool insert_course(const Course& course){
    const char* sql = R"(
        INSERT INTO courses
        (course_code, course_name, course_program,
         year_offered, lecturer_id, has_assignment)
        VALUES (?, ?, ?, ?, ?, ?);
    )";

    sqlite3_stmt* statement = nullptr;

    int resultCode = sqlite3_prepare_v2(
        db,
        sql,
        -1,
        &statement,
        nullptr
    );

    if(resultCode != SQLITE_OK)
    {
        cerr << "Failed to prepare course insertion." << endl;
        cerr << "SQLite error: "
             << sqlite3_errmsg(db) << endl;

        return false;
    }

    sqlite3_bind_text(
        statement,
        1,
        course.course_code.c_str(),
        -1,
        SQLITE_TRANSIENT
    );

    sqlite3_bind_text(
        statement,
        2,
        course.course_name.c_str(),
        -1,
        SQLITE_TRANSIENT
    );

    sqlite3_bind_text(
        statement,
        3,
        course.course_program.c_str(),
        -1,
        SQLITE_TRANSIENT
    );

    sqlite3_bind_int(
        statement,
        4,
        course.year_offered
    );

    // -1 means the course currently has no lecturer.
    if(course.lecturerID == -1)
    {
        sqlite3_bind_null(statement, 5);
    }
    else
    {
        sqlite3_bind_int(
            statement,
            5,
            course.lecturerID
        );
    }

    sqlite3_bind_int(
        statement,
        6,
        course.has_assignement ? 1 : 0
    );

    resultCode = sqlite3_step(statement);

    if(resultCode != SQLITE_DONE)
    {
        cerr << "Failed to insert course." << endl;
        cerr << "SQLite error: "
             << sqlite3_errmsg(db) << endl;

        sqlite3_finalize(statement);
        return false;
    }

    sqlite3_finalize(statement);

    cout << "Course inserted successfully." << endl;

    return true;
}

bool register_student(int studentID, const string& courseCode)
{
    const char* sql = R"(
        INSERT INTO registrations
        (student_id, course_code)
        VALUES (?, ?);
    )";

    sqlite3_stmt* statement = nullptr;

    int resultCode = sqlite3_prepare_v2(
        db,
        sql,
        -1,
        &statement,
        nullptr
    );

    if(resultCode != SQLITE_OK)
    {
        cerr << "Failed to prepare registration." << endl;
        cerr << "SQLite error: "
             << sqlite3_errmsg(db) << endl;

        return false;
    }

    sqlite3_bind_int(
        statement,
        1,
        studentID
    );

    sqlite3_bind_text(
        statement,
        2,
        courseCode.c_str(),
        -1,
        SQLITE_TRANSIENT
    );

    resultCode = sqlite3_step(statement);

    if(resultCode != SQLITE_DONE)
    {
        cerr << "Failed to register student." << endl;
        cerr << "SQLite error: "
             << sqlite3_errmsg(db) << endl;

        sqlite3_finalize(statement);
        return false;
    }

    sqlite3_finalize(statement);

    cout << "Student registered successfully." << endl;

    return true;
}

void view_registrations()
{
    const char* sql = R"(
        SELECT
            students.name,
            registrations.course_code,
            courses.course_name
        FROM registrations
        JOIN students
            ON registrations.student_id = students.student_id
        JOIN courses
            ON registrations.course_code = courses.course_code;
    )";

    sqlite3_stmt* statement = nullptr;

    int resultCode = sqlite3_prepare_v2(
        db, sql, -1, &statement, nullptr
    );

    if(resultCode != SQLITE_OK)
    {
        cerr << "Failed to prepare registration query." << endl;
        cerr << "SQLite error: " << sqlite3_errmsg(db) << endl;
        return;
    }

    cout << "\n--- Student Registrations ---\n";

    while((resultCode = sqlite3_step(statement)) == SQLITE_ROW)
    {
        const char* studentName =
            reinterpret_cast<const char*>(
                sqlite3_column_text(statement, 0)
            );

        const char* courseCode =
            reinterpret_cast<const char*>(
                sqlite3_column_text(statement, 1)
            );

        const char* courseName =
            reinterpret_cast<const char*>(
                sqlite3_column_text(statement, 2)
            );

        cout << "Student: " << studentName << endl;
        cout << "Course:  " << courseCode
             << " - " << courseName << endl;
        cout << "-----------------------------\n";
    }

    if(resultCode != SQLITE_DONE)
    {
        cerr << "Error while reading registrations." << endl;
        cerr << "SQLite error: " << sqlite3_errmsg(db) << endl;
    }

    sqlite3_finalize(statement);
}

bool insert_result(const Results& result){
     const char* sql = R"(
        INSERT INTO results
        (
            student_id,
            course_code,
            test1,
            test2,
            assignment,
            continuous_assessment,
            final_exam,
            final_mark,
            final_grade
        )
        VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?);
    )";

    sqlite3_stmt* statement = nullptr;

    int result_code = sqlite3_prepare_v2(
        db,
        sql,
        -1,
        &statement,
        nullptr
    );

    if(result_code != SQLITE_OK)
    {
        cerr << "Failed to prepare result insertion." << endl;
        cerr << "SQLite error: "
             << sqlite3_errmsg(db) << endl;
        return false;
    }

    sqlite3_bind_int(statement, 1, result.studentID);

    sqlite3_bind_text(
        statement,
        2,
        result.course_code.c_str(),
        -1,
        SQLITE_TRANSIENT
    );

    sqlite3_bind_double(statement, 3, result.test1);
    sqlite3_bind_double(statement, 4, result.test2);
    sqlite3_bind_double(statement, 5, result.assignment);
    sqlite3_bind_double(statement, 6, result.continousAssessment);
    sqlite3_bind_double(statement, 7, result.finalExam);
    sqlite3_bind_double(statement, 8, result.finalMark);

    sqlite3_bind_text(
        statement,
        9,
        result.finalGrade.c_str(),
        -1,
        SQLITE_TRANSIENT
    );

    result_code = sqlite3_step(statement);

    if(result_code != SQLITE_DONE)
    {
        cerr << "Failed to insert result." << endl;
        cerr << "SQLite error: "
             << sqlite3_errmsg(db) << endl;

        sqlite3_finalize(statement);
        return false;
    }

    sqlite3_finalize(statement);

    cout << "Result inserted successfully." << endl;

    return true;
}

bool is_student_registered(int student_id, const string& course_code){
    const char* sql = R"(
        SELECT 1
        FROM registrations
        WHERE student_id = ?
        AND course_code = ?;
    )";

    sqlite3_stmt* statement = nullptr;

    int result_code = sqlite3_prepare_v2(
        db,
        sql,
        -1,
        &statement,
        nullptr
    );

    if(result_code != SQLITE_OK)
    {
        cerr << "Failed to prepare registration check." << endl;
        cerr << "SQLite error: "
             << sqlite3_errmsg(db) << endl;

        return false;
    }

    sqlite3_bind_int(statement, 1, student_id);

    sqlite3_bind_text(
        statement,
        2,
        course_code.c_str(),
        -1,
        SQLITE_TRANSIENT
    );

    result_code = sqlite3_step(statement);

    bool registered = (result_code == SQLITE_ROW);

    sqlite3_finalize(statement);

    return registered;
}

int get_result_status(int student_id){
    // Count results for this student
    const char* results_sql = R"(
        SELECT COUNT(*) FROM results WHERE student_id = ?;
    )";

    sqlite3_stmt* statement = nullptr;
    int result_count = 0;
    int registration_count = 0;

    int result_code = sqlite3_prepare_v2(db, results_sql, -1, &statement, nullptr);
    if(result_code != SQLITE_OK){
        cerr<<"Failed to prepare result count query."<<endl;
        return 0;
    }

    sqlite3_bind_int(statement, 1, student_id);

    if(sqlite3_step(statement) == SQLITE_ROW){
        result_count = sqlite3_column_int(statement, 0);
    }
    sqlite3_finalize(statement);

    // Count registrations for this student
    const char* reg_sql = R"(
        SELECT COUNT(*) FROM registrations WHERE student_id = ?;
    )";

    result_code = sqlite3_prepare_v2(db, reg_sql, -1, &statement, nullptr);
    if(result_code != SQLITE_OK){
        cerr<<"Failed to prepare registration count query."<<endl;
        return 0;
    }

    sqlite3_bind_int(statement, 1, student_id);

    if(sqlite3_step(statement) == SQLITE_ROW){
        registration_count = sqlite3_column_int(statement, 0);
    }
    sqlite3_finalize(statement);

    // Determine status
    if(result_count == 0) return 0;
    if(result_count < registration_count) return 1;
    return 2;
}

void view_student_results(int student_id){
    int status = get_result_status(student_id);

    if(status == 0){
        cout<<"Results are not yet available.\n";
        return;
    }
    if(status == 1){
        cout<<"Results are still being processed for some courses.\n";
        return;
    }

    // status == 2, show results
    const char* sql = R"(
        SELECT
            students.name,
            results.course_code,
            courses.course_name,
            results.test1,
            results.test2,
            results.continuous_assessment,
            results.final_exam,
            results.final_mark,
            results.final_grade
        FROM results
        JOIN students ON results.student_id = students.student_id
        JOIN courses ON results.course_code = courses.course_code
        WHERE results.student_id = ?;
    )";

    sqlite3_stmt* statement = nullptr;

    int result_code = sqlite3_prepare_v2(db, sql, -1, &statement, nullptr);
    if(result_code != SQLITE_OK){
        cerr<<"Failed to prepare results query."<<endl;
        cerr<<"SQLite error: "<<sqlite3_errmsg(db)<<endl;
        return;
    }

    sqlite3_bind_int(statement, 1, student_id);

    cout<<"\n=================== My Results ===================\n";

    while((result_code = sqlite3_step(statement)) == SQLITE_ROW){
        const char* student_name =
            reinterpret_cast<const char*>(sqlite3_column_text(statement, 0));
        const char* course_code =
            reinterpret_cast<const char*>(sqlite3_column_text(statement, 1));
        const char* course_name =
            reinterpret_cast<const char*>(sqlite3_column_text(statement, 2));
        double test1           = sqlite3_column_double(statement, 3);
        double test2           = sqlite3_column_double(statement, 4);
        double ca              = sqlite3_column_double(statement, 5);
        double final_exam      = sqlite3_column_double(statement, 6);
        double final_mark      = sqlite3_column_double(statement, 7);
        const char* final_grade =
            reinterpret_cast<const char*>(sqlite3_column_text(statement, 8));

        cout<<"\nCourse: "<<course_code<<" - "<<course_name<<endl;
        cout<<"Test 1: "<<test1<<endl;
        cout<<"Test 2: "<<test2<<endl;
        cout<<"CA: "<<ca<<"/40"<<endl;
        cout<<"Final Exam: "<<final_exam<<"/60"<<endl;
        cout<<"Final Mark: "<<final_mark<<"/100"<<endl;
        cout<<"Grade: "<<(final_grade ? final_grade : "N/A")<<endl;
        cout<<"_______________________________________________\n";
    }

    if(result_code != SQLITE_DONE){
        cerr<<"Error reading results."<<endl;
        cerr<<"SQLite error: "<<sqlite3_errmsg(db)<<endl;
    }

    sqlite3_finalize(statement);
}

void delete_test_result(int student_id, const string& course_code)
{
    const char* sql = R"(
        DELETE FROM results
        WHERE student_id = ?
        AND course_code = ?;
    )";

    sqlite3_stmt* statement = nullptr;

    int result_code = sqlite3_prepare_v2(
        db,
        sql,
        -1,
        &statement,
        nullptr
    );

    if(result_code != SQLITE_OK)
    {
        cerr << "Failed to prepare test deletion." << endl;
        return;
    }

    sqlite3_bind_int(statement, 1, student_id);

    sqlite3_bind_text(
        statement,
        2,
        course_code.c_str(),
        -1,
        SQLITE_TRANSIENT
    );

    result_code = sqlite3_step(statement);

    if(result_code != SQLITE_DONE)
    {
        cerr << "Failed to delete test result." << endl;
        cerr << "SQLite error: "
             << sqlite3_errmsg(db) << endl;
    }

    sqlite3_finalize(statement);
}

void view_all_results()
{
    const char* sql = R"(
        SELECT student_id, course_code, final_mark, final_grade
        FROM results;
    )";

    sqlite3_stmt* statement = nullptr;

    int result_code = sqlite3_prepare_v2(
        db,
        sql,
        -1,
        &statement,
        nullptr
    );

    if(result_code != SQLITE_OK)
    {
        cerr << "Failed to prepare results query." << endl;
        return;
    }

    cout << "\n--- Results in Database ---\n";

    while((result_code = sqlite3_step(statement)) == SQLITE_ROW)
    {
        int student_id = sqlite3_column_int(statement, 0);

        const char* course_code =
            reinterpret_cast<const char*>(
                sqlite3_column_text(statement, 1)
            );

        double final_mark = sqlite3_column_double(statement, 2);

        const char* grade =
            reinterpret_cast<const char*>(
                sqlite3_column_text(statement, 3)
            );

        cout << "Student: " << student_id << endl;
        cout << "Course: " << course_code << endl;
        cout << "Final Mark: " << final_mark << endl;
        cout << "Grade: " << (grade ? grade : "N/A") << endl;
        cout << "--------------------------\n";
    }

    sqlite3_finalize(statement);
}
vector<Student> get_students(){


    vector<Student> students;

    const char* sql = R"(
        SELECT
            student_id,
            name,
            program,
            email,
            password,
            phone_number,
            age,
            year_of_study,
            gender
        FROM students;
    )";

    sqlite3_stmt* statement = nullptr;

    int resultCode = sqlite3_prepare_v2(
        db,
        sql,
        -1,
        &statement,
        nullptr
    );

    if(resultCode != SQLITE_OK)
    {
        cerr << "Failed to prepare student query." << endl;
        cerr << "SQLite error: " << sqlite3_errmsg(db) << endl;

        return students;
    }

    while(sqlite3_step(statement) == SQLITE_ROW)
    {
        Student student;

        student.studentID =
            sqlite3_column_int(statement, 0);

        student.name =
            reinterpret_cast<const char*>(
                sqlite3_column_text(statement, 1)
            );

        student.program =
            reinterpret_cast<const char*>(
                sqlite3_column_text(statement, 2)
            );

        student.email =
            reinterpret_cast<const char*>(
                sqlite3_column_text(statement, 3)
            );

        student.password =
            reinterpret_cast<const char*>(
                sqlite3_column_text(statement, 4)
            );

        student.phone_number =
            reinterpret_cast<const char*>(
                sqlite3_column_text(statement, 5)
            );

        student.age =
            sqlite3_column_int(statement, 6);

        student.year_of_study =
            sqlite3_column_int(statement, 7);

        const char* gender =
            reinterpret_cast<const char*>(
                sqlite3_column_text(statement, 8)
            );

        if(gender != nullptr && gender[0] != '\0')
        {
            student.gender = gender[0];
        }

        students.push_back(student);
    }

    sqlite3_finalize(statement);

    return students;
}

vector<string> get_student_courses(int student_id){
    vector<string> courses;

    const char* sql = R"(
        SELECT courses.course_code
        FROM registrations
        JOIN courses
        ON registrations.course_code = courses.course_code
        WHERE registrations.student_id = ?;
    )";

    sqlite3_stmt* statement = nullptr;

    int result_code = sqlite3_prepare_v2(db, sql, -1, &statement, nullptr);

    if(result_code != SQLITE_OK){
        cerr<<"Failed to prepare query."<<endl;
        cerr<<"SQLite error: "<<sqlite3_errmsg(db)<<endl;
        return courses;
    }

    sqlite3_bind_int(statement, 1, student_id);

    while(sqlite3_step(statement) == SQLITE_ROW){
        const char* course_code = 
            reinterpret_cast<const char*>(
                sqlite3_column_text(statement, 0)
            );
        courses.push_back(course_code);
    }

    sqlite3_finalize(statement);

    return courses;
}
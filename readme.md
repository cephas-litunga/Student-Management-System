# Student Information System

A console-based Student Information System developed in C++ and modelled around the academic workflow of Copperbelt University (CBU).

The project is being developed incrementally, with each version introducing new functionality and improvements while applying concepts learned through Computer Science studies.

## Current Version

**v1.1.0 — Result Publication Controls**

## Features

### Authentication

- Administrator login
- Student login
- Lecturer login
- Role-based access
- Password management
- Three-attempt login lockout

### Student Management

Administrators can:

- Add students
- Search students
- View all students
- Edit student details
- Edit student grades
- View student grades
- Delete students

Students can:

- View their details
- Update their information
- Change their password
- View available courses
- Register for courses
- View registered courses
- Drop courses
- View their results

### Course Management

Administrators can:

- Add courses
- View courses
- Search courses
- Edit courses
- Delete courses

Courses contain information such as:

- Course code
- Course name
- Programme
- Year offered
- Lecturer assignment

### Lecturer Management

Administrators can:

- Register lecturers
- Search lecturers
- View lecturers
- Edit lecturer details
- Delete lecturers

Lecturers can:

- View their details
- Update their information
- Change their password
- View their assigned courses
- Manage student results

### Lecturer-Course Assignment

Administrators can:

- Assign lecturers to courses
- View a lecturer's courses
- View the lecturer assigned to a course
- Remove lecturer assignments

### Course Registration

Students can:

- View available courses
- Register for courses
- View registered courses
- Drop courses

Registration checks the student's:

- Programme
- Year of study
- Existing registrations
- Maximum course limit

### Results Management

Lecturers can enter and manage student assessment results.

The system supports:

- Test 1
- Test 2
- Assignment/quiz contribution where applicable
- Continuous Assessment
- Final examination
- Final mark
- Grade calculation

The implemented assessment structure uses:

- CA out of 40
- Final examination out of 100
- Final examination contributing 60% of the final grade

### Result Publication Controls

Administrators can control whether final results are visible to students.

- Results can be published or unpublished at any time.
- The publication state persists across application restarts.
- Students see a clear message when their results exist but have not yet been published.
- Publication only affects fully completed results. Students whose registered courses are still being processed see the processing message regardless of publication state.

### Academic Reports

Administrators can generate a Course Performance Report showing, for each course:

- Number of completed results
- Number of passes (final mark 50 or above)
- Number of failures
- Pass rate

Incomplete results are excluded from the report. Courses with no completed results show `N/A` for the pass rate.

### Validation

Input validation is implemented across the major modules, including:

- Student management
- Lecturer management
- Course management
- Course registration
- Results
- Authentication

Validation helpers are centralized in `validation.h`.

## Data Storage

The system uses SQLite for persistent storage.

The database file is `sms.db` and contains the following tables:

- `students`
- `lecturers`
- `courses`
- `registrations`
- `results`
- `system_settings`

The `system_settings` table stores application-level flags such as the result publication state.

## Result Visibility Rules

Students can only view their final results when **both** of the following are true:

1. All registered courses have completed results (CA and final examination entered).
2. An administrator has published results.

A student may see one of the following messages instead of results:

| Situation | Message shown |
|---|---|
| No results entered yet | Results are not yet available. |
| Some registered courses incomplete | Results are still being processed for some courses. |
| All complete, but unpublished | Results have been entered but are not yet published by the administrator. |

## Technologies

- C++
- Object-Oriented Programming
- SQLite (via the SQLite C API)
- File-based and database-backed persistence
- Git
- GitHub

## Development

The project is developed incrementally through versioned releases.

Each version is tested before moving on to the next stage.

The long-term goal is to use this project as a foundation for developing a more complete Student Information System, including a future web-based version.

## Known Limitations

- Lecturer passwords cannot currently be reset by an administrator. Only the lecturer themselves can change their password after logging in. This is a pre-existing gap planned for a future release.

## Author

**Niza**

Computer Science Student  
Copperbelt University
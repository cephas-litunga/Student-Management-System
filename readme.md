# Student Information System

A console-based Student Information System developed in C++ and modelled around the academic workflow of Copperbelt University (CBU).

The project is being developed incrementally, with each version introducing new functionality and improvements while applying concepts learned through Computer Science studies.

## Current Version

**v1.0.0 — Continuous Assessment & Results Management**

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

The system currently uses file-based persistence.

Data is stored in:

- `students.txt`
- `courses.txt`
- `lecturers.txt`
- `registrations.txt`
- `results.txt`

## Technologies

- C++
- Object-Oriented Programming
- File Handling
- Git
- GitHub

## Development

The project is developed incrementally through versioned releases.

Each version is tested before moving on to the next stage.

The long-term goal is to use this project as a foundation for developing a more complete Student Information System, including a future web-based version.

## Author

**Niza**

Computer Science Student  
Copperbelt University
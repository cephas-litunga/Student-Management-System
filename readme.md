# Student Management System

A console-based Student Management System built in C++ as a personal project to strengthen my understanding of software development, program structure, and problem-solving.

The project started as a simple CRUD application and is gradually evolving into a university-style Student Information System with authentication, role-based access, persistent storage, and student self-service features.

---

## Features
### Authentication

- Admin login
- Student login
-Role-based access control
- Password management
- Persistent account storage

### Student Management
- Register students
- Search students by Student ID
- View all students
- Edit student details
- Delete student records
- Automatically generated unique Student IDs

### Student Profiles
- Email address
- Phone number
- Year of study
- Change password

### Academic Records
- Record grades for six subjects
- View student grades

### Data Persistence
- Save student records to files
- Load student records automatically at startup

---

## Technologies Used

* C++
* Object-Oriented Programming (OOP)
* Arrays
* Functions
* Multi-file project structure
* Command Line Interface (CLI)

--- 

## What I Learned

This project has helped me gain practical experience with:

* Organizing code across multiple source files
* Header files and linking
* Managing program state
* User input handling and validation
* Searching and updating records
* Debugging and problem-solving
* Structuring larger programs beyond a single source file

## Project Structure

```text
Student-Management-System/ │ 
├── main.cpp 
├── students.cpp 
├── students.h 
├── menus.h 
├── students.txt 
├── CHANGELOG.md 
└── README.md
```


## Current Version
[v0.5.0] - Student Profile

### Implemented:
- Student authentication
- Admin authentication
- Student profile information
- Password management
- Persistent storage
- Modular architecture

## Roadmap
- [x] Student CRUD 
- [x] Grade Management
- [x] File persistence
- [x] Authentication system
- [x] Student accounts
- [x] Admin accounts
- [x] Role-based priviledges
- [ ] Course Management
- [ ] Course Registration
- [ ] Academic Reports
- [ ] SQLite Database
- [ ] GUI Application


## Getting Started

### Compile

```bash
g++ main.cpp students.cpp -o main
```

### Run

```bash
./main
```

## Author

**Cephas Litunga**

Aspiring Software Engineer | Computer Science Student

This project is part of my journey of learning software development through hands-on practice and building in public.

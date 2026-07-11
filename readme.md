# Student Management System

A console-based Student Management System built in C++ as a personal project to strengthen my understanding of software development, program structure, and problem-solving.

The project started as a simple CRUD application and is gradually evolving into a university-style Student Information System with authentication, role-based access, persistent storage, and student self-service features.

---

## Features

### Authentication
- Administrator login
- Student login
- Lecturer login
- Password management
- Role-based access control

### Student Management
- Register students
- Search students
- View all students
- Edit student details
- Delete students
- Student profile management
- Grade management

### Course Management
- Add courses
- Search courses
- View all courses
- Edit courses
- Delete courses

### Lecturer Management
- Register lecturers
- Search lecturers
- View all lecturers
- Edit lecturer details
- Delete lecturers
- Lecturer profile management

### Lecturer-Course Assignment
- Assign lecturers to courses
- View lecturer assignments
- View course lecturer
- Remove lecturer assignments

### Data Persistence
- Save all data to text files
- Load all data when the application starts

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

--- 

## Current Project Structure

```
main.cpp
globals.h

auth.cpp
auth.h

menus.h

admin_logic.cpp
admin_logic.h

students.cpp
students.h
students_crud.cpp

courses.cpp
courses.h

lecturer.cpp
lecturer.h
lecturer_crud.cpp

assignment.cpp
```
---

## Roadmap
- [x] Student CRUD 
- [x] Grade Management
- [x] File persistence
- [x] Authentication system
- [x] Student accounts
- [x] Admin accounts
- [x] Role-based priviledges
- [x] Course Management
- [x] Lecturer Management
- [x] Lecturer-Course Assignment
- [ ] Course Registration 
- [ ] Academic Reports
- [ ] SQLite Database
- [ ] GUI Application
- [ ] Web Version

---

## Purpose 
This project is part of my journey toward becoming a software engineer. Rather than focusing only on course wrok, i'm buildig increasingly complex software to strengthen my understanding of software design, problem-solving, and application developement.

## Author

**Cephas Litunga**

Aspiring Software Engineer | Computer Science Student
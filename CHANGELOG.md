# Changelog

All notable changes to the Student Information System are documented here.

---

## [v1.0.0] — Continuous Assessment & Results Management

### Added

- Lecturer result management.
- Test 1 mark entry.
- Test 2 mark entry.
- Assignment/quiz contribution where applicable.
- Automatic Continuous Assessment calculation.
- Final examination mark entry.
- Automatic final mark calculation.
- Automatic grade calculation.
- Student result viewing.
- Result persistence.
- Three-attempt authentication lockout.

### Assessment System

- Test 1 is calculated out of 20.
- Test 2 is calculated out of 20.
- Continuous Assessment is calculated out of 40.
- Final examination is entered out of 100.
- Final examination contributes 60% to the final grade.
- Final marks are calculated automatically.
- Grades are calculated automatically.

### Validation

- Added validation for student creation and editing.
- Added validation for lecturer creation and editing.
- Added validation for course creation and editing.
- Added validation for course registration.
- Added validation for academic results.
- Added validation for authentication.

### Architecture Improvements

- Created `validation.h` to centralize validation helpers.
- Moved `validateInput()` from `menus.h` to `validation.h`.
- Changed `Student::phone_number` from `int` to `string`.
- Reworked `load_students()` to use line-by-line parsing.
- Fixed the student data loading/wipe issue.
- Moved `checkDuplicateCourse()` into `courses.cpp` as a static helper.

### Testing

- Completed feature testing.
- Completed input validation testing.
- Completed authentication testing.
- Completed persistence testing.
- Completed regression testing across existing modules.

---

## [v0.9.0] — Student Course Registration

### Added

- Student course registration.
- Available course viewing.
- Registered course viewing.
- Course dropping.
- Programme-based course validation.
- Year-of-study validation.
- Duplicate registration prevention.
- Maximum course registration limit.
- Registration persistence.

---

## [v0.8.0] — Lecturer-Course Assignment

### Added

- Lecturer-course assignment.
- View lecturer's courses.
- View course lecturer.
- Remove lecturer assignments.

---

## [v0.7.0] — Lecturer Management

### Added

- Lecturer registration.
- Lecturer viewing.
- Lecturer searching.
- Lecturer editing.
- Lecturer deletion.
- Lecturer authentication.
- Lecturer portal.
- Lecturer profile management.
- Lecturer password management.

---

## [v0.6.0] — Course Management

### Added

- Course creation.
- Course viewing.
- Course searching.
- Course editing.
- Course deletion.
- Course persistence.
- Course programme information.
- Course year information.
- Lecturer assignment field.

---

## [v0.5.0] — Student Management Improvements

### Added

- Student profile information.
- Student year of study.
- Student programme.
- Student contact information.
- Improved student management.

---

## [v0.4.0] — Student Portal

### Added

- Student details viewing.
- Student information updates.
- Password changes.
- Student grade viewing.

---

## [v0.3.0] — Authentication & Role-Based Access

### Added

- Administrator authentication.
- Student authentication.
- Role-based menus.
- Role-based access.

---

## [v0.2.0] — Student Management

### Added

- Student records.
- Student creation.
- Student viewing.
- Student searching.
- Student editing.
- Student deletion.
- Student data persistence.

---

## [v0.1.0] — Project Foundation

### Added

- Initial C++ project.
- Basic project structure.
- Student class.
- Initial application flow.
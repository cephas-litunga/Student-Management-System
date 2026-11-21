# Changelog

All notable changes to the Student Information System are documented here.

## [v1.2.0] — Administrative Password Reset

### Added

- Admin menu action to reset a student's password.
- Admin menu action to reset a lecturer's password.
- Confirmation prompt before applying a password reset.
- In-memory synchronisation so the new password is immediately usable within the same running session.

### Changed

- Admin menu extended from 6 to 8 options (Logout renumbered to 8).
- Admin menu now groups account-management actions (`Reset Student Password`, `Reset Lecturer Password`) alongside the existing feature areas.

### Architecture

- Reused existing `update_student_password` and `update_lecturer_password` database helpers rather than adding new SQL. This keeps password-writing logic in one place for any future change (e.g. password hashing).
- Deliberately avoided a single `reset_user_password("students" | "lecturers", ...)` helper. Parameterising table names requires SQL string concatenation, which undermines the prepared-statement safety pattern used throughout the codebase.

### Testing

- Verified admin reset for a student (260005) and a lecturer (1003), including persistence.
- Verified the old password stops working and the new one succeeds.
- Verified in-memory sync by resetting and re-logging-in within a single running session.
- Verified the cancel path leaves the database untouched.
- Verified clean handling of non-existent IDs.
- Verified that the existing user-initiated password change flows for both students and lecturers still work (regression check after touching `auth.cpp`).
- Verified that resetting a password to its current value succeeds (SQLite reports a change even for identical values on this version).

---


## [v1.1.0] — Result Publication Controls

### Added

- Persistent result publication flag stored in SQLite (`system_settings` table).
- Administrator control to publish and unpublish results.
- Student result view now respects publication state.
- `get_result_status()` extended with a new `3` status meaning "results complete but unpublished".
- `get_results_published()` and `set_results_published()` database helpers.

### Changed

- Admin menu extended from 5 to 6 options (Publish / Unpublish Results added as option 5; Logout renumbered to 6).
- Student view distinguishes between:
  - "Results are not yet available" (status `0` — nothing entered).
  - "Results are still being processed for some courses" (status `1` — partial completion).
  - "Results have been entered but are not yet published by the administrator" (status `3` — complete but withheld).
  - Normal results listing (status `2` — complete and published).

### Behaviour

- On first run against an existing database, the `system_settings` table is created and seeded with `results_published = '0'` (unpublished), which is the safe default. Existing `sms.db` files are migrated in place — no data loss.
- Completion checking takes priority over publication state: a student whose registered courses are not all complete still sees the "processing" message, regardless of publication.
- Publication state persists across application restarts because it is stored in SQLite, not in memory.

### Testing

- Verified publication gating for a fully complete student (Alice, 260001) across all states.
- Verified persistence across application restart.
- Verified partial-completion priority over publication state (Brian, 260002).

### Known Limitations

- Lecturer passwords cannot currently be reset by an administrator. Only the lecturer themselves can change their password after logging in. This is a pre-existing gap, not introduced in this release, and is deferred to a future version.

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
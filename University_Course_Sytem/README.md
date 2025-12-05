# University Course Registration System

A comprehensive course registration and management system built with Qt and C++. This application allows administrators, instructors, and students to manage course registrations, view schedules, and generate reports.

## Features

### User Roles

#### Admin
- Create and manage student accounts
- Create and manage instructor accounts
- Add, edit, and delete courses
- View system statistics and analysis
- Generate reports (student schedules, course enrollment, instructor workloads)
- Export reports to TXT files

#### Instructor
- View assigned courses with full details
- View course schedules
- View enrollment lists for assigned courses
- See student information for each course

#### Student
- Register for courses
- Drop courses
- View personal schedule
- Search for available courses
- Automatic waitlist management for full courses

### Key Features

- **User Authentication**: Secure login system with role-based access
- **Course Management**: Full CRUD operations for courses
- **Schedule Conflict Detection**: Prevents students from registering for conflicting courses
- **Waitlist System**: Automatic enrollment when space becomes available
- **Data Persistence**: All data stored in text files for easy backup and portability
- **Search Functionality**: Search courses by various criteria
- **Statistics Dashboard**: Comprehensive system analytics
- **Report Generation**: Export detailed reports in TXT format

## Team & Workload Distribution

This project was developed by a team of 4 members with the following workload distribution:

### Areege
- **Admin Dashboard** (main interface)
  - Admin dashboard UI design and layout
  - Add/Delete/List functionality for students, courses, and instructors
  - Integration of admin features
  - *Note: Analytics and summary statistics were handled separately*

### Abdullah
- **Student Window & Features**
  - Student main window interface
  - Course registration functionality
  - Drop courses feature
  - View schedule implementation
  - Student-specific UI components

### Judy
- **Course Management & Instructor Features**
  - Course class implementation
  - Course CRUD operations (Create, Read, Update, Delete)
  - Instructor window and interface
  - Instructor schedule view
  - Instructor courses view
  - View enrollment functionality
  - Course-instructor relationship management

### Omar
- **Admin Dashboard Extensions & User Handling**
  - Statistics and analytics window
  - Reports generation and export functionality
  - User authentication and login system
  - Password validation and security
  - File I/O and data persistence
  - Registration system core functionality
  - User session management

## Setup Instructions Using Qt Creator

1. Open Qt Creator
2. File → Open File or Project
3. Select `University_Course_Sytem.pro`
4. Click "Configure Project"
5. Click the "Build" button (or press Ctrl+B)
6. Click the "Run" button (or press Ctrl+R)


### 4. Initial Setup
On first run, the system will create default admin account:
- **Username**: Admin1, **Password**: 123

The system will also create the following data files in the project directory:
- `Students.txt` - Student data
- `Instructors.txt` - Instructor data
- `courses.txt` - Course data
- `admins.txt` - Admin account data

## Usage Examples

### Admin Login

1. Launch the application
2. Enter admin credentials 
3. Access the admin dashboard

### Creating a Student Account (Admin)

1. Log in as admin
2. Click "Add Student"
3. Fill in:
   - Name
   - Student ID
   - Email
   - Password (minimum 8 characters, must contain a number)
4. Click "Done"

### Creating a Course (Admin)

1. Log in as admin
2. Click "Add Course"
3. Fill in:
   - Course ID
   - Course Name
   - Credit Hours
   - Max Enrollment
   - Schedule Time
   - Department
   - Instructor ID
4. Click "Done"

### Registering for a Course (Student)

1. Log in as student
2. Click "Register Course"
3. Browse available courses in the table
4. Use the search box to find specific courses
5. Select a course from the table
6. Click "Register"
7. The system will:
   - Check for schedule conflicts
   - Check if already registered
   - Enroll or add to waitlist if full

### Viewing Statistics (Admin)

1. Log in as admin
2. Click "View Statistics"
3. View:
   - Summary statistics (total courses, students, instructors)
   - Course enrollment table
   - Instructor workload table

### Generating Reports (Admin)

1. Log in as admin
2. Click "Generate Reports"
3. Select report type:
   - **Student Schedules**: All students and their registered courses
   - **Course Enrollment**: All courses with enrolled and waitlisted students
   - **Instructor Workload**: All instructors with assigned courses and student counts
4. Click "Export as TXT" to save the report

### Viewing Schedule (Student)

1. Log in as student
2. Click "View Schedule"
3. See all registered courses sorted by time slot

### Viewing Assigned Courses (Instructor)

1. Log in as instructor
2. Click "View courses"
3. See all assigned courses with full details

#include "registration_system.h"
#include <fstream>
#include <QString>
#include <iostream>
using namespace std;

Registration_System::Registration_System() {}

void Registration_System::savestudents(const QString &filename) {
    //rebuild password map
    studentPasswords.clear();
    for (const auto &student : studentList) {
        studentPasswords[student.email.toStdString()] = student.password.toStdString();
    }
    
ofstream file(filename.toStdString());
    if (!file.is_open()) {
cerr << "Failed to open file for writing: " << filename.toStdString() << endl;
        return;
    }
    
    for (const auto &student : studentList) {
        //write student info
        file << student.name.toStdString() << " " 
             << student.id.toStdString() << " " 
             << student.email.toStdString() << " " 
             << student.password.toStdString() << " "
             << student.registered.size() << "\n";
        
        //write registered courses
        for (const auto &course : student.registered) {
            file << course.id.toStdString() << " "
                 << course.name.toStdString() << " "
                 << course.timeSlot.toStdString() << "\n";
        }
    }
    
    file.close();
}

void Registration_System::loadstudents(const QString &filename) {
ifstream file(filename.toStdString());
    if (!file.is_open()) {
cerr << "Failed to open file for reading: " << filename.toStdString() << endl;
        return;
    }
    
    studentList.clear();
    studentPasswords.clear();
    
    //load courses first to get full details
    loadcourses();
    
string name, id, email, password;
    int numCourses;
    
    while (file >> name >> id >> email >> password) {
        //create student
        Student newStudent(
            QString::fromStdString(name), 
            QString::fromStdString(email), 
            QString::fromStdString(id), 
            QString::fromStdString(password)
        );
        studentList.push_back(newStudent);
        studentPasswords[email] = password;
        
        //check if has courses
        if (file >> numCourses && numCourses > 0) {
            Student &student = studentList.back();
            
            //load registered courses
            for (int i = 0; i < numCourses; i++) {
string courseId, courseName, courseTime;
                if (file >> courseId >> courseName >> courseTime) {
                    QString qCourseId = QString::fromStdString(courseId);
                    
                    //try find full course details
                    bool foundFullCourse = false;
                    for (const auto &fullCourse : courseList) {
                        if (fullCourse.id == qCourseId) {
                            //use full course details
                            student.registered.push_back(fullCourse);
                            foundFullCourse = true;
                            break;
                        }
                    }
                    
                    //if not found create minimal course
                    if (!foundFullCourse) {
                        student.registered.emplace_back(
                            qCourseId,
                            QString::fromStdString(courseName),
                            "", "", 0, QString::fromStdString(courseTime), 0
                        );
                    }
                }
            }
        }
        //old format, no courses
    }
    
    file.close();
}

void Registration_System::saveinstructors(const QString &filename) {
    //rebuild password map
    instructorPasswords.clear();
    for (const auto &instructor : instructorList) {
        instructorPasswords[instructor.Email.toStdString()] = instructor.instructorPassword.toStdString();
    }
    
ofstream file(filename.toStdString());
    if (!file.is_open()) {
cerr << "Failed to open file for writing: " << filename.toStdString() << endl;
        return;
    }
    
    for (const auto &instructor : instructorList) {
        file << instructor.Name.toStdString() << " " 
             << instructor.InstructorId.toStdString() << " " 
             << instructor.Email.toStdString() << " " 
             << instructor.instructorPassword.toStdString() << " "
             << instructor.assignedCourses.size();
        //write assigned course ids
        for (const auto &courseId : instructor.assignedCourses) {
            file << " " << courseId.toStdString();
        }
        file << "\n";
    }
    
    file.close();
}

void Registration_System::loadinstructors(const QString &filename) {
ifstream file(filename.toStdString());
    if (!file.is_open()) {
cerr << "Failed to open file for reading: " << filename.toStdString() << endl;
        return;
    }
    
    instructorList.clear();
    instructorPasswords.clear();
    
string name, id, email, password;
    while (file >> name >> id >> email >> password) {
        //create instructor from file
        instructorList.emplace_back(
            QString::fromStdString(name), 
            QString::fromStdString(email), 
            QString::fromStdString(id), 
            QString::fromStdString(password)
        );
        instructorPasswords[email] = password;
        
        //read assigned courses count
        int numCourses;
        if (file >> numCourses) {
            //read course ids
            for (int i = 0; i < numCourses; i++) {
                string courseId;
                if (file >> courseId) {
                    instructorList.back().assignedCourses.push_back(QString::fromStdString(courseId));
                }
            }
        }
    }
    
    file.close();
}

void Registration_System::savecourses(const QString &filename) {
ofstream file(filename.toStdString());
    if (!file.is_open()) {
cerr << "Failed to open file for writing: " << filename.toStdString() << endl;
        return;
    }
    
    for (const auto &course : courseList) {
        //save course info
        file << course.id.toStdString() << " " 
             << course.name.toStdString() << " " 
             << course.instructor.toStdString() << " "
             << course.department.toStdString() << " "
             << course.creditHours << " "
             << course.timeSlot.toStdString() << " "
             << course.maxEnrollment << " "
             << course.enrolledStudents.size() << " ";
        
        //save enrolled students
        for (const Student &student : course.enrolledStudents) {
            file << student.name.toStdString() << " "
                 << student.email.toStdString() << " "
                 << student.id.toStdString() << " ";
        }
        
        //save waitlist
        file << course.waitingList.size() << " ";
        for (const Student &student : course.waitingList) {
            file << student.name.toStdString() << " "
                 << student.email.toStdString() << " "
                 << student.id.toStdString() << " ";
        }
        
        file << "\n";
    }
    
    file.close();
}

void Registration_System::loadcourses(const QString &filename) {
ifstream file(filename.toStdString());
    if (!file.is_open()) {
cerr << "Failed to open file for reading: " << filename.toStdString() << endl;
        return;
    }
    
    courseList.clear();
    
string id, name, instructor, department, timeSlot;
    int credits = 0, maxEnroll = 0;
    
    //read from file
    while (file >> id >> name >> instructor >> department >> credits >> timeSlot >> maxEnroll) {
        Course course(
            QString::fromStdString(id),
            QString::fromStdString(name),
            QString::fromStdString(instructor),
            QString::fromStdString(department),
            credits,
            QString::fromStdString(timeSlot),
            maxEnroll
        );
        
        //read enrolled count
        int enrolledCount = 0;
        if (file >> enrolledCount) {
            //read enrolled students
            for (int i = 0; i < enrolledCount; i++) {
string studentName, studentEmail, studentId;
                if (file >> studentName >> studentEmail >> studentId) {
                    course.enrolledStudents.push_back(Student(
                        QString::fromStdString(studentName),
                        QString::fromStdString(studentEmail),
                        QString::fromStdString(studentId),
                        ""  //no password needed
                    ));
                }
            }
        }
        
        //read waitlist
        int waitListCount = 0;
        if (file >> waitListCount) {
            for (int i = 0; i < waitListCount; i++) {
string studentName, studentEmail, studentId;
                if (file >> studentName >> studentEmail >> studentId) {
                    course.waitingList.push_back(Student(
                        QString::fromStdString(studentName),
                        QString::fromStdString(studentEmail),
                        QString::fromStdString(studentId),
                        ""  //no password needed
                    ));
                }
            }
        }
        
        courseList.push_back(course);
    }
    
    file.close();
}

void Registration_System::loadadmins(const QString &filename) {
    ifstream file(filename.toStdString());
    if (!file.is_open()) {
        cerr << "Failed to open file for reading: " << filename.toStdString() << endl;
        //create default admin if file doesn't exist
        adminPasswords["Admin1"] = "123";
        adminPasswords["Admin2"] = "456";
        return;
    }
    
    adminPasswords.clear();
    string username, password;
    while (file >> username >> password) {
        adminPasswords[username] = password;
    }
    
    file.close();
    
    //if no admins loaded, create default ones
    if (adminPasswords.empty()) {
        adminPasswords["Admin1"] = "123";
    }
}

//global instance
Registration_System r;

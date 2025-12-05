#include "registration_system.h"
#include <fstream>
#include <QString>
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

Registration_System::Registration_System() {}

void Registration_System::savestudents(const QString &filename) {
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
        file << student.firstName.toStdString() << " " 
             << student.lastName.toStdString() << " "
             << student.id.toStdString() << " " 
             << student.email.toStdString() << " " 
             << student.password.toStdString() << " "
             << student.registered.size() << "\n";
        
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
    
    loadcourses();
    
    string firstName, lastName, id, email, password;
    int numCourses;
    
    while (file >> firstName >> lastName >> id >> email >> password) {
        Student newStudent(
            QString::fromStdString(firstName), 
            QString::fromStdString(lastName),
            QString::fromStdString(email), 
            QString::fromStdString(id), 
            QString::fromStdString(password)
        );
        studentList.push_back(newStudent);
        studentPasswords[email] = password;
        
        if (file >> numCourses && numCourses > 0) {
            Student &student = studentList.back();
            
            for (int i = 0; i < numCourses; i++) {
string courseId, courseName, courseTime;
                if (file >> courseId >> courseName >> courseTime) {
                    QString qCourseId = QString::fromStdString(courseId);
                    
                    bool foundFullCourse = false;
                    for (const auto &fullCourse : courseList) {
                        if (fullCourse.id == qCourseId) {
                            student.registered.push_back(fullCourse);
                            foundFullCourse = true;
                            break;
                        }
                    }
                    
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
    }
    
    file.close();
}

void Registration_System::saveinstructors(const QString &filename) {
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
        file << instructor.FirstName.toStdString() << " " 
             << instructor.LastName.toStdString() << " "
             << instructor.InstructorId.toStdString() << " " 
             << instructor.Email.toStdString() << " " 
             << instructor.instructorPassword.toStdString() << " "
             << instructor.assignedCourses.size();
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
    
    string firstName, lastName, id, email, password;
    int numCourses;
    
    while (file >> firstName >> lastName >> id >> email >> password) {
        instructorList.emplace_back(
            QString::fromStdString(firstName), 
            QString::fromStdString(lastName),
            QString::fromStdString(email), 
            QString::fromStdString(id), 
            QString::fromStdString(password)
        );
        instructorPasswords[email] = password;
        
        if (file >> numCourses) {
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
        file << course.id.toStdString() << " " 
             << course.name.toStdString() << " " 
             << course.instructorId.toStdString() << " "
             << course.department.toStdString() << " "
             << course.creditHours << " "
             << course.timeSlot.toStdString() << " "
             << course.maxEnrollment << " "
             << course.enrolledStudents.size() << " ";
        
        for (const Student &student : course.enrolledStudents) {
            file << student.firstName.toStdString() << " "
                 << student.lastName.toStdString() << " "
                 << student.email.toStdString() << " "
                 << student.id.toStdString() << " ";
        }
        
        file << course.waitingList.size() << " ";
        for (const Student &student : course.waitingList) {
            file << student.firstName.toStdString() << " "
                 << student.lastName.toStdString() << " "
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
    
    string id, name, instructorId, department, timeSlot;
    int credits = 0, maxEnroll = 0;
    
    while (file >> id >> name >> instructorId >> department >> credits >> timeSlot >> maxEnroll) {
        Course course(
            QString::fromStdString(id),
            QString::fromStdString(name),
            QString::fromStdString(instructorId),
            QString::fromStdString(department),
            credits,
            QString::fromStdString(timeSlot),
            maxEnroll
        );
        
        int enrolledCount = 0;
        if (file >> enrolledCount) {
            for (int i = 0; i < enrolledCount; i++) {
string studentFirstName, studentLastName, studentEmail, studentId;
                if (file >> studentFirstName >> studentLastName >> studentEmail >> studentId) {
                    course.enrolledStudents.push_back(Student(
                        QString::fromStdString(studentFirstName),
                        QString::fromStdString(studentLastName),
                        QString::fromStdString(studentEmail),
                        QString::fromStdString(studentId),
                        ""
                    ));
                }
            }
        }
        
        int waitListCount = 0;
        if (file >> waitListCount) {
            for (int i = 0; i < waitListCount; i++) {
string studentFirstName, studentLastName, studentEmail, studentId;
                if (file >> studentFirstName >> studentLastName >> studentEmail >> studentId) {
                    course.waitingList.push_back(Student(
                        QString::fromStdString(studentFirstName),
                        QString::fromStdString(studentLastName),
                        QString::fromStdString(studentEmail),
                        QString::fromStdString(studentId),
                        ""
                    ));
                }
            }
        }
        
        courseList.push_back(course);
    }
    
    file.close();
}

QString Registration_System::getInstructorName(const QString &instructorId) const {
    for (const auto &instructor : instructorList) {
        if (instructor.InstructorId == instructorId) {
            return instructor.FirstName + " " + instructor.LastName;
        }
    }
    return instructorId;
}

void Registration_System::loadadmins(const QString &filename) {
    ifstream file(filename.toStdString());
    if (!file.is_open()) {
        cerr << "Failed to open file for reading: " << filename.toStdString() << endl;
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
    
    if (adminPasswords.empty()) {
        adminPasswords["Admin1"] = "123";
    }
}

Registration_System r;

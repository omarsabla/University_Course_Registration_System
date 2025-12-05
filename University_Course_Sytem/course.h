#ifndef COURSE_H
#define COURSE_H

#include <QString>
#include <vector>

class Student;
using namespace std;

class Course {
public:
    QString id;
    QString name;
    QString instructorId;
    QString department;
    int creditHours;
    QString timeSlot;
    int maxEnrollment;
    vector<Student> enrolledStudents;
    vector<Student> waitingList;

    Course() = default;
    Course(QString id, QString name, QString instrId, QString dept, int credits, QString time, int maxEnroll);
    bool isFull() const;
    void enrollStudent(const Student &student);
    void dropStudent(const QString &studentId);
    QString toString() const;
    static Course fromString(const QString& line);
};

#endif

#ifndef COURSE_H
#define COURSE_H

#include <QString>
#include <vector>
// Don't include student.h here - it will be included before course.h in files that need both
// This breaks the circular dependency
class Student;
using namespace std;

class Course {
public:
    QString id;
    QString name;
    QString instructor;
    QString department;
    int creditHours;
    QString timeSlot;
    int maxEnrollment;
    vector<Student> enrolledStudents;
    vector<Student> waitingList;

    Course() = default;
    Course(QString id, QString name, QString instr, QString dept, int credits, QString time, int maxEnroll);
    bool isFull() const;
    void enrollStudent(const Student &student);
    void dropStudent(const QString &studentId);
    QString toString() const;
    static Course fromString(const QString& line);
};

#endif

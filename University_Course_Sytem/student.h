#ifndef STUDENT_H
#define STUDENT_H

#include <QString>
#include <vector>


#include "course.h"
using namespace std;

class Student {
public:
    QString firstName, lastName, email, id, password ;

    vector<Course> registered;

    Student(const QString &firstName, const QString &lastName, const QString &email, const QString &id, const QString &password);

    bool hasTimeConflict(const Course &c);
    bool alreadyRegistered(const Course &c);
    void addCourse(const Course &c);
};

#endif

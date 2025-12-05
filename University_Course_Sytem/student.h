#ifndef STUDENT_H
#define STUDENT_H

#include <QString>
#include <vector>
// Include course.h - the circular dependency is handled by include guards
// When course.h includes student.h, Student will be fully defined
#include "course.h"
using namespace std;

class Student {
public:
    QString name, email, id, password ;

    vector<Course> registered;

    Student(const QString &name, const QString &email, const QString &id, const QString &password);

    bool hasTimeConflict(const Course &c);
    bool alreadyRegistered(const Course &c);
    void addCourse(const Course &c);
};

#endif

#ifndef STUDENT_H
#define STUDENT_H

#include <QString>
#include <vector>
#include "course.h"

class Student {
public:
    QString username;
    std::vector<Course> registered;

    Student() {}
    Student(QString user) : username(user) {}

    bool hasTimeConflict(const Course &c) {
        for (const auto &reg : registered)
            if (reg.timeSlot == c.timeSlot)
                return true;
        return false;
    }

    bool alreadyRegistered(const Course &c) {
        for (const auto &reg : registered)
            if (reg.id == c.id)
                return true;
        return false;
    }

    void addCourse(const Course &c) { registered.push_back(c); }
};

#endif

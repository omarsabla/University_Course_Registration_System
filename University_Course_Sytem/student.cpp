#include "student.h"
#include "course.h"

//Student::Student() {}

Student::Student(const QString &name, const QString &email, const QString &id, const QString &password) : name(name), email(email), id(id), password(password) {}

bool Student::hasTimeConflict(const Course &c) {
    for (const auto &reg : registered)
        if (reg.timeSlot == c.timeSlot)
            return true;
    return false;
}

bool Student::alreadyRegistered(const Course &c) {
    for (const auto &reg : registered)
        if (reg.id == c.id)
            return true;
    return false;
}

void Student::addCourse(const Course &c) {
    registered.push_back(c);
}

#include "course.h"
// course.cpp
#include "course.h"

Course::Course(QString id, QString name, QString instr, QString dept, int credits, QString time, int maxEnroll)
    : id(std::move(id)),
    name(std::move(name)),
    instructor(std::move(instr)),
    department(std::move(dept)),
    creditHours(credits),
    timeSlot(std::move(time)),
    maxEnrollment(maxEnroll) {}

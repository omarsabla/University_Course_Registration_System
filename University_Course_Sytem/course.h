#ifndef COURSE_H
#define COURSE_H

#include <QString>

class Course {
public:
    QString id;
    QString name;
    QString timeSlot;

    Course() {}
    Course(QString _id, QString _name, QString _timeSlot)
        : id(_id), name(_name), timeSlot(_timeSlot) {}
};

#endif

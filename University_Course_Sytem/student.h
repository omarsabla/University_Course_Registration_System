#ifndef STUDENT_H
#define STUDENT_H
#include <QString>

class Student
{
    QString name;
    QString id;
    QString email;
    QString studentPassword;
    QString* courses[];

public:
   void registerCourse();
    void dropCourse();
    void viewSchedule();
    void checkScheduleConflict();

    Student();
};

#endif // STUDENT_H

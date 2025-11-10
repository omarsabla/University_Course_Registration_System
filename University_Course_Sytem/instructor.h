#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H
#include <QString>
class Instructor
{
    QString InstructorId;
    QString Name;
    QString Email;
    QString instructorPassword;

    QString* assignedCourses[];

public:
    Instructor();
    void assignCourses();
    void viewCourses();
    void trackEnrollment();

};

#endif // INSTRUCTOR_H

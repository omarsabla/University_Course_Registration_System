#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H
#include <QString>
#include <vector>
using namespace std;

class Instructor
{
public:
    QString InstructorId;
    QString FirstName;
    QString LastName;
    QString Email;
    QString instructorPassword;
    vector<QString> assignedCourses;

    Instructor();
    Instructor(const QString &firstName, const QString &lastName, const QString &email, const QString &id, const QString &password);
    void assignCourses();
    void viewCourses();
    void trackEnrollment();

};

#endif 

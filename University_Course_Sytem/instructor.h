#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H
#include <QString>
#include <vector>
using namespace std;

class Instructor
{
public:
    QString InstructorId;
    QString Name;
    QString Email;
    QString instructorPassword;
    vector<QString> assignedCourses;  // Vector of course IDs

    Instructor();
    Instructor(const QString &name, const QString &email, const QString &id, const QString &password);
    void assignCourses();
    void viewCourses();
    void trackEnrollment();

};

#endif // INSTRUCTOR_H

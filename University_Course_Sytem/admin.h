#ifndef ADMIN_H
#define ADMIN_H
#include <QString>
class Admin
{
    QString adminID;
    QString name;
    QString email;
    QString password;
public:
    Admin();
    void addCourse();
    void removeCourse();
    void addStudent();
    void removeStudent();
    void addInstructor();
    void removeInstructor();
};

#endif // ADMIN_H

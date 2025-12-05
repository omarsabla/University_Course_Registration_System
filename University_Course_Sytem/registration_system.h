#ifndef REGISTRATION_SYSTEM_H
#define REGISTRATION_SYSTEM_H
#include <vector>
#include <map>
//include student first so its defined before course uses it
#include "student.h"
#include "course.h"  //student already defined so vector works
#include "admin.h"
#include "instructor.h"
#include <string>

using namespace std;
class Registration_System
{





public:
    map < string , string> studentPasswords;
    map < string , string > adminPasswords;
    map < string , string > instructorPasswords;
    vector<Student> studentList;
    vector<Admin> adminList;
    vector<Course> courseList;
    vector<Instructor> instructorList;

    Registration_System();
    
    void savestudents(const QString &filename = "/Users/yasser/University_Course_Registration_System/University_Course_Sytem/Students.txt");
    void loadstudents(const QString &filename = "/Users/yasser/University_Course_Registration_System/University_Course_Sytem/Students.txt");
    void saveinstructors(const QString &filename = "/Users/yasser/University_Course_Registration_System/University_Course_Sytem/Instructors.txt");
    void loadinstructors(const QString &filename = "/Users/yasser/University_Course_Registration_System/University_Course_Sytem/Instructors.txt");
    void savecourses(const QString &filename = "/Users/yasser/University_Course_Registration_System/University_Course_Sytem/courses.txt");
    void loadcourses(const QString &filename = "/Users/yasser/University_Course_Registration_System/University_Course_Sytem/courses.txt");
    void loadadmins(const QString &filename = "/Users/yasser/University_Course_Registration_System/University_Course_Sytem/admins.txt");
};

#endif // REGISTRATION_SYSTEM_H
extern Registration_System r;


#ifndef REGISTRATION_SYSTEM_H
#define REGISTRATION_SYSTEM_H
#include <vector>
#include <map>
#include "student.h"
#include "admin.h"
#include "course.h"
#include "admin.h"
#include "instructor.h"
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
};

#endif // REGISTRATION_SYSTEM_H

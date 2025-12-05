#include "instructor.h"

Instructor::Instructor() {}

Instructor::Instructor(const QString &firstName, const QString &lastName, const QString &email, const QString &id, const QString &password)
    : FirstName(firstName), LastName(lastName), Email(email), InstructorId(id), instructorPassword(password) {}

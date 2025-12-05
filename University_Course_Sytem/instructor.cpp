#include "instructor.h"

Instructor::Instructor() {}

Instructor::Instructor(const QString &name, const QString &email, const QString &id, const QString &password)
    : Name(name), Email(email), InstructorId(id), instructorPassword(password) {}

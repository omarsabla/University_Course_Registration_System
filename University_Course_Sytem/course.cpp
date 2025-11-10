#include "Course.h"

Course::Course(QString id, QString name, QString instr, QString dept, int credits, QString time, int maxEnroll)
    : courseID(id), courseName(name), instructor(instr), department(dept),
    creditHours(credits), scheduleTime(time), maxEnrollment(maxEnroll) {}

bool Course::isFull() const {
    return enrolledStudents.size() >= maxEnrollment;
}

void Course::enrollStudent(QString studentUsername) {
    if (!isFull()) {
        enrolledStudents.append(studentUsername);
    } else {
        waitingList.append(studentUsername);
    }
}

void Course::dropStudent(QString studentUsername) {
    enrolledStudents.removeAll(studentUsername);
    if (!waitingList.isEmpty()) {
        enrolledStudents.append(waitingList.takeFirst());
    }
}

QString Course::toString() const {
    return QString("%1|%2|%3|%4|%5|%6|%7")
    .arg(courseID)
        .arg(courseName)
        .arg(instructor)
        .arg(department)
        .arg(creditHours)
        .arg(scheduleTime)
        .arg(maxEnrollment);
}

Course Course::fromString(const QString& line) {
    QStringList parts = line.split("|");
    if (parts.size() < 7) return {};
    return Course(parts[0], parts[1], parts[2], parts[3], parts[4].toInt(), parts[5], parts[6].toInt());
}

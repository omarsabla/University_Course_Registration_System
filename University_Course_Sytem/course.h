#ifndef COURSE_H
#define COURSE_H

#include <QString>
#include <QList>

class Course {
public:
    QString id;
    QString name;
    QString instructor;
    QString department;
    int creditHours;
    QString timeSlot;
    int maxEnrollment;
    QList<QString> enrolledStudents;
    QList<QString> waitingList;

    Course() = default;
    Course(QString id, QString name, QString instr, QString dept, int credits, QString time, int maxEnroll);
    bool isFull() const;
    void enrollStudent(QString studentUsername);
    void dropStudent(QString studentUsername);
    QString toString() const;
    static Course fromString(const QString& line);
};

#endif

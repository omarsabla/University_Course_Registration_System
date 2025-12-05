#include "student.h"
#include "course.h"

Course::Course(QString id, QString name, QString instrId, QString dept, int credits, QString time, int maxEnroll)
    : id(move(id)),
    name(move(name)),
    instructorId(move(instrId)),
    department(move(dept)),
    creditHours(credits),
    timeSlot(move(time)),
    maxEnrollment(maxEnroll) {}

bool Course::isFull() const {
    return enrolledStudents.size() >= maxEnrollment;
}

void Course::enrollStudent(const Student &student) {
    for (const auto &enrolled : enrolledStudents) {
        if (enrolled.id == student.id) {
            return;
        }
    }
    
    for (const auto &waiting : waitingList) {
        if (waiting.id == student.id) {
            return;
        }
    }
    
    if (isFull()) {
        waitingList.push_back(student);
    } else {
        enrolledStudents.push_back(student);
    }
}

void Course::dropStudent(const QString &studentId) {
    for (auto it = enrolledStudents.begin(); it != enrolledStudents.end(); ) {
        if (it->id == studentId) {
            it = enrolledStudents.erase(it);
            
            if (!waitingList.empty() && !isFull()) {
                Student firstWaiting = waitingList.front();
                waitingList.erase(waitingList.begin());
                enrolledStudents.push_back(firstWaiting);
            }
            return;
        } else {
            ++it;
        }
    }
    
    for (auto it = waitingList.begin(); it != waitingList.end(); ) {
        if (it->id == studentId) {
            it = waitingList.erase(it);
            return;
        } else {
            ++it;
        }
    }
}

//include student first
#include "student.h"
#include "course.h"

Course::Course(QString id, QString name, QString instr, QString dept, int credits, QString time, int maxEnroll)
    : id(move(id)),
    name(move(name)),
    instructor(move(instr)),
    department(move(dept)),
    creditHours(credits),
    timeSlot(move(time)),
    maxEnrollment(maxEnroll) {}

bool Course::isFull() const {
    return enrolledStudents.size() >= maxEnrollment;
}

void Course::enrollStudent(const Student &student) {
    //check if already enrolled
    for (const auto &enrolled : enrolledStudents) {
        if (enrolled.id == student.id) {
            return;  //already enrolled
        }
    }
    
    //check if on waitlist
    for (const auto &waiting : waitingList) {
        if (waiting.id == student.id) {
            return;  //already on waitlist
        }
    }
    
    //if full add to waitlist
    if (isFull()) {
        waitingList.push_back(student);
    } else {
        //add to enrolled
        enrolledStudents.push_back(student);
    }
}

void Course::dropStudent(const QString &studentId) {
    //remove from enrolled
    for (auto it = enrolledStudents.begin(); it != enrolledStudents.end(); ) {
        if (it->id == studentId) {
            it = enrolledStudents.erase(it);
            
            //if waitlist has space move first to enrolled
            if (!waitingList.empty() && !isFull()) {
                Student firstWaiting = waitingList.front();
                waitingList.erase(waitingList.begin());
                enrolledStudents.push_back(firstWaiting);
            }
            return;  //found and removed
        } else {
            ++it;
        }
    }
    
    //remove from waitlist
    for (auto it = waitingList.begin(); it != waitingList.end(); ) {
        if (it->id == studentId) {
            it = waitingList.erase(it);
            return;  //found and removed
        } else {
            ++it;
        }
    }
}

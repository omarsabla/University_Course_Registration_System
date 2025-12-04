// Include student.h first to ensure Student is fully defined before Course uses it
#include "student.h"
#include "course.h"

Course::Course(QString id, QString name, QString instr, QString dept, int credits, QString time, int maxEnroll)
    : id(std::move(id)),
    name(std::move(name)),
    instructor(std::move(instr)),
    department(std::move(dept)),
    creditHours(credits),
    timeSlot(std::move(time)),
    maxEnrollment(maxEnroll) {}

bool Course::isFull() const {
    return enrolledStudents.size() >= maxEnrollment;
}

void Course::enrollStudent(const Student &student) {
    // Check if student is already enrolled (by ID)
    for (const auto &enrolled : enrolledStudents) {
        if (enrolled.id == student.id) {
            return;  // Already enrolled
        }
    }

    // Check if student is already on wait list
    for (const auto &waiting : waitingList) {
        if (waiting.id == student.id) {
            return;  // Already on wait list
        }
    }

    // If course is full, add to wait list
    if (isFull()) {
        waitingList.push_back(student);
    } else {
        // Add to enrolled students
        enrolledStudents.push_back(student);
    }
}

void Course::dropStudent(const QString &studentId) {
    // Remove from enrolled students using simple loop
    for (auto it = enrolledStudents.begin(); it != enrolledStudents.end(); ) {
        if (it->id == studentId) {
            it = enrolledStudents.erase(it);

            // If there's a wait list and now there's space, move first student from wait list to enrolled
            if (!waitingList.empty() && !isFull()) {
                Student firstWaiting = waitingList.front();
                waitingList.erase(waitingList.begin());
                enrolledStudents.push_back(firstWaiting);
            }
            return;  // Found and removed, exit
        } else {
            ++it;
        }
    }

    // Remove from wait list if not enrolled
    for (auto it = waitingList.begin(); it != waitingList.end(); ) {
        if (it->id == studentId) {
            it = waitingList.erase(it);
            return;  // Found and removed, exit
        } else {
            ++it;
        }
    }
}

#include "reportspage.h"
#include "ui_reportspage.h"
#include "registration_system.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>

ReportsPage::ReportsPage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ReportsPage)
    , currentReport("")
{
    ui->setupUi(this);
    
    
    r.loadstudents();
    r.loadcourses();
    r.loadinstructors();
}

ReportsPage::~ReportsPage()
{
    delete ui;
}

void ReportsPage::on_StudentSchedules_Button_clicked()
{
    generateStudentSchedulesReport();
}

void ReportsPage::on_CourseEnrollment_Button_clicked()
{
    generateCourseEnrollmentReport();
}

void ReportsPage::on_InstructorWorkload_Button_clicked()
{
    generateInstructorWorkloadReport();
}

void ReportsPage::on_Export_Button_clicked()
{
    if (currentReport.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please generate a report first.");
        return;
    }
    exportReport("txt");
}

void ReportsPage::on_Done_Button_clicked()
{
    hide();
}

void ReportsPage::generateStudentSchedulesReport()
{
    QString report = "STUDENT SCHEDULES REPORT\n";
    report += "==========================================\n\n";
    
    for (const auto &student : r.studentList) {
        report += QString("Student: %1 %2 (ID: %3, Email: %4)\n").arg(student.firstName, student.lastName, student.id, student.email);
        report += "Registered Courses:\n";
        
        if (student.registered.empty()) {
            report += "  No courses registered.\n";
        } else {
            for (const auto &course : student.registered) {
                report += QString("  - %1 (%2) - %3\n").arg(course.name, course.id, course.timeSlot);
            }
        }
        report += "\n";
    }
    
    ui->textEdit->setPlainText(report);
    currentReport = report;
}

void ReportsPage::generateCourseEnrollmentReport()
{
    QString report = "COURSE ENROLLMENT REPORT\n";
    report += "==========================================\n\n";
    
    for (const auto &course : r.courseList) {
        report += QString("Course: %1 (%2)\n").arg(course.name, course.id);
        report += QString("Instructor: %1\n").arg(r.getInstructorName(course.instructorId));
        report += QString("Department: %1\n").arg(course.department);
        report += QString("Time Slot: %1\n").arg(course.timeSlot);
        report += QString("Enrollment: %1/%2\n").arg(course.enrolledStudents.size()).arg(course.maxEnrollment);
        report += QString("Waitlist: %1\n").arg(course.waitingList.size());
        report += "Enrolled Students:\n";
        
        if (course.enrolledStudents.empty()) {
            report += "  No students enrolled.\n";
        } else {
            for (const auto &student : course.enrolledStudents) {
                report += QString("  - %1 %2 (%3) - %4\n").arg(student.firstName, student.lastName, student.id, student.email);
            }
        }
        
        if (!course.waitingList.empty()) {
            report += "Waitlisted Students:\n";
            for (const auto &student : course.waitingList) {
                report += QString("  - %1 %2 (%3) - %4\n").arg(student.firstName, student.lastName, student.id, student.email);
            }
        }
        report += "\n";
    }
    
    ui->textEdit->setPlainText(report);
    currentReport = report;
}

void ReportsPage::generateInstructorWorkloadReport()
{
    QString report = "INSTRUCTOR WORKLOAD REPORT\n";
    report += "==========================================\n\n";
    
    for (const auto &instructor : r.instructorList) {
        report += QString("Instructor: %1 %2 (ID: %3, Email: %4)\n").arg(instructor.FirstName, instructor.LastName, instructor.InstructorId, instructor.Email);
        report += "Assigned Courses:\n";
        
        if (instructor.assignedCourses.empty()) {
            report += "  No courses assigned.\n";
        } else {
            int totalEnrollment = 0;
            for (const QString &courseId : instructor.assignedCourses) {
                
                for (const auto &course : r.courseList) {
                    if (course.id == courseId) {
                        report += QString("  - %1 (%2) - %3 students enrolled\n")
                                 .arg(course.name, course.id)
                                 .arg(course.enrolledStudents.size());
                        totalEnrollment += course.enrolledStudents.size();
                        break;
                    }
                }
            }
            report += QString("Total Courses: %1\n").arg(instructor.assignedCourses.size());
            report += QString("Total Students: %1\n").arg(totalEnrollment);
        }
        report += "\n";
    }
    
    ui->textEdit->setPlainText(report);
    currentReport = report;
}

void ReportsPage::exportReport(const QString &format)
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save Report", "", "Text Files (*.txt)");
    if (fileName.isEmpty()) {
        return;
    }
    
    
    if (!fileName.endsWith(".txt", Qt::CaseInsensitive)) {
        fileName += ".txt";
    }
    
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Failed to save file.");
        return;
    }
    
    QTextStream out(&file);
    out << currentReport;
    
    file.close();
    QMessageBox::information(this, "Success", "Report exported successfully.");
}


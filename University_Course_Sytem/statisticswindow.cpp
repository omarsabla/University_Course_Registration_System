#include "statisticswindow.h"
#include "ui_statisticswindow.h"
#include "registration_system.h"
#include <QTableWidgetItem>

StatisticsWindow::StatisticsWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::StatisticsWindow)
{
    ui->setupUi(this);
    
    //load data
    r.loadstudents();
    r.loadcourses();
    r.loadinstructors();
    
    //update statistics
    updateStatistics();
}

StatisticsWindow::~StatisticsWindow()
{
    delete ui;
}

void StatisticsWindow::on_Done_Button_clicked()
{
    hide();
}

void StatisticsWindow::updateStatistics()
{
    //calculate statistics
    int totalCourses = r.courseList.size();
    int totalStudents = r.studentList.size();
    int totalInstructors = r.instructorList.size();
    
    //calculate total enrolled students across all courses
    int totalEnrolled = 0;
    for (const auto &course : r.courseList) {
        totalEnrolled += course.enrolledStudents.size();
    }
    
    //calculate average students per course
    double avgStudentsPerCourse = totalCourses > 0 ? (double)totalEnrolled / totalCourses : 0.0;
    
    //calculate instructor workloads (courses per instructor)
    double avgCoursesPerInstructor = totalInstructors > 0 ? (double)totalCourses / totalInstructors : 0.0;
    
    //update summary label
    QString summary = QString("Summary Statistics:\n\n")
                     + QString("Total Courses: %1\n").arg(totalCourses)
                     + QString("Total Students: %1\n").arg(totalStudents)
                     + QString("Total Instructors: %1\n").arg(totalInstructors)
                     + QString("Total Enrollments: %1\n").arg(totalEnrolled)
                     + QString("Average Students per Course: %1\n").arg(QString::number(avgStudentsPerCourse, 'f', 1))
                     + QString("Average Courses per Instructor: %1").arg(QString::number(avgCoursesPerInstructor, 'f', 1));
    
    ui->summaryLabel->setText(summary);
    
    //populate course enrollment table
    QTableWidget *courseTable = ui->courseTableWidget;
    courseTable->setColumnCount(4);
    QStringList headers;
    headers << "Course ID" << "Course Name" << "Enrolled" << "Capacity";
    courseTable->setHorizontalHeaderLabels(headers);
    
    courseTable->setRowCount(totalCourses);
    for (int i = 0; i < totalCourses; ++i) {
        const Course &course = r.courseList[i];
        courseTable->setItem(i, 0, new QTableWidgetItem(course.id));
        courseTable->setItem(i, 1, new QTableWidgetItem(course.name));
        courseTable->setItem(i, 2, new QTableWidgetItem(QString::number(course.enrolledStudents.size())));
        courseTable->setItem(i, 3, new QTableWidgetItem(QString::number(course.maxEnrollment)));
        
        //make items non-editable
        for (int j = 0; j < 4; j++) {
            QTableWidgetItem *item = courseTable->item(i, j);
            if (item) {
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            }
        }
    }
    
    courseTable->resizeColumnsToContents();
    courseTable->setAlternatingRowColors(true);
    courseTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    
    //populate instructor workload table
    QTableWidget *instructorTable = ui->instructorTableWidget;
    instructorTable->setColumnCount(4);
    QStringList instructorHeaders;
    instructorHeaders << "Instructor ID" << "Instructor Name" << "Assigned Courses" << "Total Students";
    instructorTable->setHorizontalHeaderLabels(instructorHeaders);
    
    instructorTable->setRowCount(totalInstructors);
    for (int i = 0; i < totalInstructors; ++i) {
        const Instructor &instructor = r.instructorList[i];
        instructorTable->setItem(i, 0, new QTableWidgetItem(instructor.InstructorId));
        instructorTable->setItem(i, 1, new QTableWidgetItem(instructor.Name));
        instructorTable->setItem(i, 2, new QTableWidgetItem(QString::number(instructor.assignedCourses.size())));
        
        //calculate total students for this instructor
        int totalStudentsForInstructor = 0;
        for (const QString &courseId : instructor.assignedCourses) {
            for (const auto &course : r.courseList) {
                if (course.id == courseId) {
                    totalStudentsForInstructor += course.enrolledStudents.size();
                    break;
                }
            }
        }
        instructorTable->setItem(i, 3, new QTableWidgetItem(QString::number(totalStudentsForInstructor)));
        
        //make items non-editable
        for (int j = 0; j < 4; j++) {
            QTableWidgetItem *item = instructorTable->item(i, j);
            if (item) {
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            }
        }
    }
    
    instructorTable->resizeColumnsToContents();
    instructorTable->setAlternatingRowColors(true);
    instructorTable->setSelectionBehavior(QAbstractItemView::SelectRows);
}


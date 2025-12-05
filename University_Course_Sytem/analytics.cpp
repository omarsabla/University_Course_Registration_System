#include "analytics.h"
#include "ui_analytics.h"
#include "registration_system.h"
#include <QTableWidgetItem>
#include <QColor>
#include <vector>

Analytics::Analytics(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Analytics)
{
    ui->setupUi(this);
    
    
    r.loadstudents();
    r.loadcourses();
    r.loadinstructors();
    
    
    updateStatistics();
}

Analytics::~Analytics()
{
    delete ui;
}

void Analytics::on_Done_Button_clicked()
{
    hide();
}

void Analytics::updateStatistics()
{
    
    int totalCourses = r.courseList.size();
    int totalStudents = r.studentList.size();
    
    
    int totalEnrolled = 0;
    for (const auto &course : r.courseList) {
        totalEnrolled += course.enrolledStudents.size();
    }
    
    
    double avgStudentsPerCourse = totalCourses > 0 ? (double)totalEnrolled / totalCourses : 0.0;
    
    
    QString summary = QString("Summary Statistics:\n\n")
                     + QString("Total Courses: %1\n").arg(totalCourses)
                     + QString("Total Students: %1\n").arg(totalStudents)
                     + QString("Total Registered Students (across all courses): %1\n").arg(totalEnrolled)
                     + QString("Average Registered Students per Course: %1").arg(QString::number(avgStudentsPerCourse, 'f', 1));
    
    ui->summaryLabel->setText(summary);
    
    
    populatePopularCoursesTable();
    populateWaitlistTable();
    populateInstructorMetricsTable();
}

void Analytics::populatePopularCoursesTable()
{
    
    std::vector<std::pair<int, const Course*>> coursesWithEnrollment;
    for (const auto &course : r.courseList) {
        coursesWithEnrollment.push_back({course.enrolledStudents.size(), &course});
    }
    
    
    for (size_t i = 0; i < coursesWithEnrollment.size(); i++) {
        for (size_t j = 0; j < coursesWithEnrollment.size() - 1 - i; j++) {
            if (coursesWithEnrollment[j].first < coursesWithEnrollment[j + 1].first) {
                
                auto temp = coursesWithEnrollment[j];
                coursesWithEnrollment[j] = coursesWithEnrollment[j + 1];
                coursesWithEnrollment[j + 1] = temp;
            }
        }
    }
    
    
    QTableWidget *table = ui->popularCoursesTableWidget;
    table->setColumnCount(6);
    QStringList headers;
    headers << "Course ID" << "Course Name" << "Instructor" << "Enrolled" << "Capacity" << "Enrollment %";
    table->setHorizontalHeaderLabels(headers);
    
    int displayCount = coursesWithEnrollment.size() > 10 ? 10 : coursesWithEnrollment.size();
    table->setRowCount(displayCount);
    
    for (int i = 0; i < displayCount; ++i) {
        const Course *course = coursesWithEnrollment[i].second;
        table->setItem(i, 0, new QTableWidgetItem(course->id));
        table->setItem(i, 1, new QTableWidgetItem(course->name));
        table->setItem(i, 2, new QTableWidgetItem(course->instructorId));
        table->setItem(i, 3, new QTableWidgetItem(QString::number(course->enrolledStudents.size())));
        table->setItem(i, 4, new QTableWidgetItem(QString::number(course->maxEnrollment)));
        
        
        double enrollmentPercent = course->maxEnrollment > 0 ? 
            (double)course->enrolledStudents.size() / course->maxEnrollment * 100.0 : 0.0;
        int barLength = (int)(enrollmentPercent / 2.0); 
        QChar filledChar(0x2588); 
        QChar emptyChar(0x2591); 
        QString bar = QString(barLength, filledChar) + QString(50 - barLength, emptyChar);
        QString percentText = QString::number(enrollmentPercent, 'f', 1) + "% " + bar;
        table->setItem(i, 5, new QTableWidgetItem(percentText));
        
        
        for (int j = 0; j < 6; j++) {
            QTableWidgetItem *item = table->item(i, j);
            if (item) {
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            }
        }
        
        
        if (enrollmentPercent >= 90) {
            
            for (int j = 0; j < 6; j++) {
                table->item(i, j)->setBackground(QColor(200, 255, 200));
            }
        } else if (enrollmentPercent >= 70) {
            
            for (int j = 0; j < 6; j++) {
                table->item(i, j)->setBackground(QColor(255, 255, 200));
            }
        }
    }
    
    table->resizeColumnsToContents();
    table->setAlternatingRowColors(false);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void Analytics::populateWaitlistTable()
{
    
    std::vector<std::pair<int, const Course*>> coursesWithWaitlist;
    for (const auto &course : r.courseList) {
        if (course.waitingList.size() > 0) {
            coursesWithWaitlist.push_back({course.waitingList.size(), &course});
        }
    }
    
    
    for (size_t i = 0; i < coursesWithWaitlist.size(); i++) {
        for (size_t j = 0; j < coursesWithWaitlist.size() - 1 - i; j++) {
            if (coursesWithWaitlist[j].first < coursesWithWaitlist[j + 1].first) {
                
                auto temp = coursesWithWaitlist[j];
                coursesWithWaitlist[j] = coursesWithWaitlist[j + 1];
                coursesWithWaitlist[j + 1] = temp;
            }
        }
    }
    
    
    QTableWidget *table = ui->waitlistTableWidget;
    table->setColumnCount(6);
    QStringList headers;
    headers << "Course ID" << "Course Name" << "Instructor" << "Waitlist Size" << "Enrolled/Capacity" << "Waitlist Bar";
    table->setHorizontalHeaderLabels(headers);
    
    int displayCount = coursesWithWaitlist.size() > 10 ? 10 : coursesWithWaitlist.size();
    table->setRowCount(displayCount);
    
    for (int i = 0; i < displayCount; ++i) {
        const Course *course = coursesWithWaitlist[i].second;
        table->setItem(i, 0, new QTableWidgetItem(course->id));
        table->setItem(i, 1, new QTableWidgetItem(course->name));
        table->setItem(i, 2, new QTableWidgetItem(course->instructorId));
        int waitlistSize = course->waitingList.size();
        table->setItem(i, 3, new QTableWidgetItem(QString::number(waitlistSize)));
        QString enrollInfo = QString::number(course->enrolledStudents.size()) + "/" + QString::number(course->maxEnrollment);
        table->setItem(i, 4, new QTableWidgetItem(enrollInfo));
        
        
        int maxWaitlist = 20; 
        int barLength = waitlistSize > maxWaitlist ? 50 : (int)((double)waitlistSize / maxWaitlist * 50.0);
        QChar filledChar(0x2588); 
        QChar emptyChar(0x2591); 
        QString bar = QString(barLength, filledChar) + QString(50 - barLength, emptyChar);
        table->setItem(i, 5, new QTableWidgetItem(bar));
        
        
        for (int j = 0; j < 6; j++) {
            QTableWidgetItem *item = table->item(i, j);
            if (item) {
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            }
        }
        
        
        if (waitlistSize >= 10) {
            for (int j = 0; j < 6; j++) {
                table->item(i, j)->setBackground(QColor(255, 200, 200));
            }
        } else if (waitlistSize >= 5) {
            for (int j = 0; j < 6; j++) {
                table->item(i, j)->setBackground(QColor(255, 240, 200));
            }
        }
    }
    
    table->resizeColumnsToContents();
    table->setAlternatingRowColors(false);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void Analytics::populateInstructorMetricsTable()
{
    QTableWidget *table = ui->instructorTableWidget;
    table->setColumnCount(6);
    QStringList headers;
    headers << "Instructor ID" << "Instructor Name" << "Number of Courses" << "Average Enrollment" << "Total Waitlist Size" << "Status";
    table->setHorizontalHeaderLabels(headers);
    
    int totalInstructors = r.instructorList.size();
    table->setRowCount(totalInstructors);
    
    
    double avgCoursesPerInstructor = totalInstructors > 0 ? 
        (double)r.courseList.size() / totalInstructors : 0.0;
    
    
    int totalEnrollment = 0;
    for (const auto &course : r.courseList) {
        totalEnrollment += course.enrolledStudents.size();
    }
    double avgEnrollmentPerInstructor = totalInstructors > 0 ? 
        (double)totalEnrollment / totalInstructors : 0.0;
    
    for (int i = 0; i < totalInstructors; ++i) {
        const Instructor &instructor = r.instructorList[i];
        table->setItem(i, 0, new QTableWidgetItem(instructor.InstructorId));
        table->setItem(i, 1, new QTableWidgetItem(instructor.FirstName + " " + instructor.LastName));
        
        int numCourses = instructor.assignedCourses.size();
        table->setItem(i, 2, new QTableWidgetItem(QString::number(numCourses)));
        
        
        int totalStudentsForInstructor = 0;
        int totalWaitlistForInstructor = 0;
        for (const QString &courseId : instructor.assignedCourses) {
            for (const auto &course : r.courseList) {
                if (course.id == courseId) {
                    totalStudentsForInstructor += course.enrolledStudents.size();
                    totalWaitlistForInstructor += course.waitingList.size();
                    break;
                }
            }
        }
        
        double avgEnrollment = numCourses > 0 ? (double)totalStudentsForInstructor / numCourses : 0.0;
        table->setItem(i, 3, new QTableWidgetItem(QString::number(avgEnrollment, 'f', 1)));
        table->setItem(i, 4, new QTableWidgetItem(QString::number(totalWaitlistForInstructor)));
        
        
        QString status;
        bool isOverloaded = false;
        bool isUnderutilized = false;
        
        if (numCourses > avgCoursesPerInstructor * 1.5 || avgEnrollment > avgEnrollmentPerInstructor * 1.5) {
            status = "Overloaded";
            isOverloaded = true;
        } else if (numCourses < avgCoursesPerInstructor * 0.5 || avgEnrollment < avgEnrollmentPerInstructor * 0.5) {
            status = "Underutilized";
            isUnderutilized = true;
        } else {
            status = "Normal";
        }
        
        table->setItem(i, 5, new QTableWidgetItem(status));
        
        
        for (int j = 0; j < 6; j++) {
            QTableWidgetItem *item = table->item(i, j);
            if (item) {
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            }
        }
        
        
        if (isOverloaded) {
            
            for (int j = 0; j < 6; j++) {
                table->item(i, j)->setBackground(QColor(255, 150, 150));
                table->item(i, j)->setForeground(QColor(0, 0, 0)); 
            }
        } else if (isUnderutilized) {
            
            for (int j = 0; j < 6; j++) {
                table->item(i, j)->setBackground(QColor(255, 220, 150));
                table->item(i, j)->setForeground(QColor(0, 0, 0)); 
            }
        } else {
            
            for (int j = 0; j < 6; j++) {
                table->item(i, j)->setBackground(QColor(150, 255, 150));
                table->item(i, j)->setForeground(QColor(0, 0, 0)); 
            }
        }
    }
    
    table->resizeColumnsToContents();
    table->setAlternatingRowColors(false);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
}

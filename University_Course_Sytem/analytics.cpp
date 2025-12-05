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
    
    //load data
    r.loadstudents();
    r.loadcourses();
    r.loadinstructors();
    
    //update statistics
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
    //calculate summary statistics
    int totalCourses = r.courseList.size();
    int totalStudents = r.studentList.size();
    
    //calculate total registered students across all courses
    int totalEnrolled = 0;
    for (const auto &course : r.courseList) {
        totalEnrolled += course.enrolledStudents.size();
    }
    
    //calculate average registered students per course
    double avgStudentsPerCourse = totalCourses > 0 ? (double)totalEnrolled / totalCourses : 0.0;
    
    //update summary label
    QString summary = QString("Summary Statistics:\n\n")
                     + QString("Total Courses: %1\n").arg(totalCourses)
                     + QString("Total Students: %1\n").arg(totalStudents)
                     + QString("Total Registered Students (across all courses): %1\n").arg(totalEnrolled)
                     + QString("Average Registered Students per Course: %1").arg(QString::number(avgStudentsPerCourse, 'f', 1));
    
    ui->summaryLabel->setText(summary);
    
    //populate all tables
    populatePopularCoursesTable();
    populateWaitlistTable();
    populateInstructorMetricsTable();
}

void Analytics::populatePopularCoursesTable()
{
    //create a vector of courses with enrollment info for sorting
    std::vector<std::pair<int, const Course*>> coursesWithEnrollment;
    for (const auto &course : r.courseList) {
        coursesWithEnrollment.push_back({course.enrolledStudents.size(), &course});
    }
    
    //sort by enrollment (descending) - manual bubble sort
    for (size_t i = 0; i < coursesWithEnrollment.size(); i++) {
        for (size_t j = 0; j < coursesWithEnrollment.size() - 1 - i; j++) {
            if (coursesWithEnrollment[j].first < coursesWithEnrollment[j + 1].first) {
                //manual swap
                auto temp = coursesWithEnrollment[j];
                coursesWithEnrollment[j] = coursesWithEnrollment[j + 1];
                coursesWithEnrollment[j + 1] = temp;
            }
        }
    }
    
    //populate table
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
        table->setItem(i, 2, new QTableWidgetItem(course->instructor));
        table->setItem(i, 3, new QTableWidgetItem(QString::number(course->enrolledStudents.size())));
        table->setItem(i, 4, new QTableWidgetItem(QString::number(course->maxEnrollment)));
        
        //calculate enrollment percentage and create bar chart
        double enrollmentPercent = course->maxEnrollment > 0 ? 
            (double)course->enrolledStudents.size() / course->maxEnrollment * 100.0 : 0.0;
        int barLength = (int)(enrollmentPercent / 2.0); //scale to 50 chars max
        QChar filledChar(0x2588); // full block
        QChar emptyChar(0x2591); // light shade
        QString bar = QString(barLength, filledChar) + QString(50 - barLength, emptyChar);
        QString percentText = QString::number(enrollmentPercent, 'f', 1) + "% " + bar;
        table->setItem(i, 5, new QTableWidgetItem(percentText));
        
        //make items non-editable
        for (int j = 0; j < 6; j++) {
            QTableWidgetItem *item = table->item(i, j);
            if (item) {
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            }
        }
        
        //color code based on enrollment percentage
        if (enrollmentPercent >= 90) {
            //high enrollment - green
            for (int j = 0; j < 6; j++) {
                table->item(i, j)->setBackground(QColor(200, 255, 200));
            }
        } else if (enrollmentPercent >= 70) {
            //medium-high enrollment - yellow
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
    //create a vector of courses with waitlist info for sorting
    std::vector<std::pair<int, const Course*>> coursesWithWaitlist;
    for (const auto &course : r.courseList) {
        if (course.waitingList.size() > 0) {
            coursesWithWaitlist.push_back({course.waitingList.size(), &course});
        }
    }
    
    //sort by waitlist size (descending) - manual bubble sort
    for (size_t i = 0; i < coursesWithWaitlist.size(); i++) {
        for (size_t j = 0; j < coursesWithWaitlist.size() - 1 - i; j++) {
            if (coursesWithWaitlist[j].first < coursesWithWaitlist[j + 1].first) {
                //manual swap
                auto temp = coursesWithWaitlist[j];
                coursesWithWaitlist[j] = coursesWithWaitlist[j + 1];
                coursesWithWaitlist[j + 1] = temp;
            }
        }
    }
    
    //populate table
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
        table->setItem(i, 2, new QTableWidgetItem(course->instructor));
        int waitlistSize = course->waitingList.size();
        table->setItem(i, 3, new QTableWidgetItem(QString::number(waitlistSize)));
        QString enrollInfo = QString::number(course->enrolledStudents.size()) + "/" + QString::number(course->maxEnrollment);
        table->setItem(i, 4, new QTableWidgetItem(enrollInfo));
        
        //create bar chart for waitlist (scale to max 50)
        int maxWaitlist = 20; //assume max waitlist of 20 for scaling
        int barLength = waitlistSize > maxWaitlist ? 50 : (int)((double)waitlistSize / maxWaitlist * 50.0);
        QChar filledChar(0x2588); // full block
        QChar emptyChar(0x2591); // light shade
        QString bar = QString(barLength, filledChar) + QString(50 - barLength, emptyChar);
        table->setItem(i, 5, new QTableWidgetItem(bar));
        
        //make items non-editable
        for (int j = 0; j < 6; j++) {
            QTableWidgetItem *item = table->item(i, j);
            if (item) {
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            }
        }
        
        //color code - red for high waitlist
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
    
    //calculate average courses per instructor for comparison
    double avgCoursesPerInstructor = totalInstructors > 0 ? 
        (double)r.courseList.size() / totalInstructors : 0.0;
    
    //calculate average enrollment per instructor for comparison
    int totalEnrollment = 0;
    for (const auto &course : r.courseList) {
        totalEnrollment += course.enrolledStudents.size();
    }
    double avgEnrollmentPerInstructor = totalInstructors > 0 ? 
        (double)totalEnrollment / totalInstructors : 0.0;
    
    for (int i = 0; i < totalInstructors; ++i) {
        const Instructor &instructor = r.instructorList[i];
        table->setItem(i, 0, new QTableWidgetItem(instructor.InstructorId));
        table->setItem(i, 1, new QTableWidgetItem(instructor.Name));
        
        int numCourses = instructor.assignedCourses.size();
        table->setItem(i, 2, new QTableWidgetItem(QString::number(numCourses)));
        
        //calculate average enrollment and total waitlist for this instructor
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
        
        //determine status: overloaded or underutilized
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
        
        //make items non-editable
        for (int j = 0; j < 6; j++) {
            QTableWidgetItem *item = table->item(i, j);
            if (item) {
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            }
        }
        
        //color code based on status
        if (isOverloaded) {
            //red background for overloaded - darker for better contrast
            for (int j = 0; j < 6; j++) {
                table->item(i, j)->setBackground(QColor(255, 150, 150));
                table->item(i, j)->setForeground(QColor(0, 0, 0)); //black text
            }
        } else if (isUnderutilized) {
            //yellow background for underutilized - darker for better contrast
            for (int j = 0; j < 6; j++) {
                table->item(i, j)->setBackground(QColor(255, 220, 150));
                table->item(i, j)->setForeground(QColor(0, 0, 0)); //black text
            }
        } else {
            //green background for normal - darker for better contrast
            for (int j = 0; j < 6; j++) {
                table->item(i, j)->setBackground(QColor(150, 255, 150));
                table->item(i, j)->setForeground(QColor(0, 0, 0)); //black text
            }
        }
    }
    
    table->resizeColumnsToContents();
    table->setAlternatingRowColors(false);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
}

#include "studentwindow.h"
#include "ui_studentwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QTableWidgetItem>
#include "registration_system.h"
#include "student.h"
#include "registercourse.h"
#include "dropcoursewindow.h"
#include "viewschedule.h"

StudentWindow::StudentWindow(const QString &studentUsername, QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::StudentWindow),
    currentStudent("", "", studentUsername, "", "")
{
    ui->setupUi(this);
    
    
    r.loadstudents();
    
    
    bool found = false;
    for (const auto &student : r.studentList) {
        if (student.email == studentUsername) {
            currentStudent = student;
            found = true;
            break;
        }
    }
    
    if (!found) {
        
        QMessageBox::warning(this, "Warning", "Student data not found. Some features may not work.");
    }

    
    ui->welcome_Message->setText("Welcome " + currentStudent.firstName + " " + currentStudent.lastName);

    loadCoursesFromFile();
    fillAvailableCoursesTable();
    fillMyCoursesTable();
    
    
    r.loadcourses();
}

StudentWindow::~StudentWindow()
{
    delete ui;
}

void StudentWindow::loadCoursesFromFile()
{
    allCourses.clear();

    
    r.loadcourses();
    
    
    for (const auto &course : r.courseList) {
        allCourses.append(course);
    }
}



void StudentWindow::on_registercourse_Button_clicked()
{
    
    r.loadstudents();
    for (const auto &student : r.studentList) {
        if (student.id == currentStudent.id) {
            currentStudent = student;
            break;
        }
    }
    
    registercourse* RC = new registercourse(currentStudent, this);
    RC->show();
}

void StudentWindow::fillAvailableCoursesTable()
{
    
    r.loadcourses();
    
    
    loadCoursesFromFile();
    
    
}

void StudentWindow::fillMyCoursesTable()
{
    
    r.loadstudents();
    
    
    for (const auto &student : r.studentList) {
        if (student.id == currentStudent.id) {
            currentStudent = student;
            break;
        }
    }
    
    
}

void StudentWindow::on_registerButton_clicked()
{
    
    QMessageBox::information(this, "Register", "Course registration functionality");
}

void StudentWindow::on_pushButton_clicked()
{
    
    QMessageBox::information(this, "Action", "Button clicked");
}


void StudentWindow::on_pushButton_3_clicked()
{

}


void StudentWindow::on_Drop_Course_Button_clicked()
{
    
    r.loadstudents();
    for (const auto &student : r.studentList) {
        if (student.id == currentStudent.id) {
            currentStudent = student;
            break;
        }
    }
    
    dropcoursewindow* DCW = new dropcoursewindow(currentStudent, this);
    DCW->show();
}


void StudentWindow::on_pushButton_2_clicked()
{
    
    r.loadstudents();
    for (const auto &student : r.studentList) {
        if (student.id == currentStudent.id) {
            currentStudent = student;
            break;
        }
    }
    
    viewschedule* VS = new viewschedule(currentStudent, this);
    VS->show();
}


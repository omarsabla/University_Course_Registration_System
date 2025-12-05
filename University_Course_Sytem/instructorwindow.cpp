#include "instructorwindow.h"
#include "ui_instructorwindow.h"
#include "instructorschedule.h"
#include "instructorcourses.h"
#include "viewenrollment.h"
#include "registration_system.h"

InstructorWindow::InstructorWindow(const QString &instructorEmail, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InstructorWindow)
    , instructorEmail(instructorEmail)
{
    ui->setupUi(this);
    
    //load instructors to get instructor name
    r.loadinstructors();
    
    //find instructor and set welcome message
    QString instructorName = "Instructor";
    for (const auto &instructor : r.instructorList) {
        if (instructor.Email == instructorEmail) {
            instructorName = instructor.Name;
            break;
        }
    }
    
    //set welcome message
    ui->label->setText("Welcome " + instructorName);
}

InstructorWindow::~InstructorWindow()
{
    delete ui;
}

void InstructorWindow::on_pushButton_clicked()
{
    instructorschedule* IS = new instructorschedule(instructorEmail, this);
    IS->show();
}

void InstructorWindow::on_viewcourses_clicked()
{
    instructorcourses* IC = new instructorcourses(instructorEmail, this);
    IC->show();
}

void InstructorWindow::on_viewenrollment_clicked()
{
    viewenrollment* VE = new viewenrollment(instructorEmail, this);
    VE->show();
}


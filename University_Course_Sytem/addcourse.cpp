#include "addcourse.h"
#include "ui_addcourse.h"
#include <iostream>
#include <fstream>
#include <QMessageBox>
#include "registration_system.h"
#include "course.h"

AddCourse::AddCourse(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddCourse)
{
    ui->setupUi(this);
}

AddCourse::~AddCourse()
{
    delete ui;
}

void AddCourse::on_done_push_Button_clicked()
{
    QString name = ui->nameLE->text();
    QString id = ui->idLE->text();
    QString creditStr = ui->cdLE->text();
    QString enrollmentStr = ui->meLE->text();
    QString schedule = ui->stLE->text();
    QString department = ui->Department->text();
    QString instructorId = ui->instrcutor_ID->text();

    //validate fields
    if (name.isEmpty() || id.isEmpty() || creditStr.isEmpty() || 
        enrollmentStr.isEmpty() || schedule.isEmpty() || department.isEmpty() || instructorId.isEmpty()) {
        QMessageBox::warning(this, "Error", "All fields must be filled out.");
        return;
    }

    //convert to int
    bool creditOk, enrollmentOk;
    int creditHours = creditStr.toInt(&creditOk);
    int maxEnrollment = enrollmentStr.toInt(&enrollmentOk);

    if (!creditOk || !enrollmentOk || creditHours <= 0 || maxEnrollment <= 0) {
        QMessageBox::warning(this, "Error", "Credit hours and max enrollment must be positive numbers.");
        return;
    }

    //check if course id exists
    r.loadcourses();
    for (const auto &course : r.courseList) {
        if (course.id == id) {
            QMessageBox::warning(this, "Error", "A course with this ID already exists.");
            return;
        }
    }

    //load instructors
    r.loadinstructors();
    
    //find instructor by id
    QString instructorName = "";
    bool instructorFound = false;
    int instructorIndex = -1;
    for (size_t i = 0; i < r.instructorList.size(); i++) {
        if (r.instructorList[i].InstructorId == instructorId) {
            instructorName = r.instructorList[i].Name;
            instructorIndex = i;
            instructorFound = true;
            break;
        }
    }
    
    if (!instructorFound) {
        QMessageBox::warning(this, "Error", "Instructor with this ID does not exist.");
        return;
    }

    //create new course
    Course newCourse(id, name, instructorName, department, creditHours, schedule, maxEnrollment);
    r.courseList.push_back(newCourse);
    
    //add course to instructor
    r.instructorList[instructorIndex].assignedCourses.push_back(id);
    
    //save courses and instructors
    r.savecourses();
    r.saveinstructors();

    QMessageBox::information(this, "Success", "Course added successfully and assigned to " + instructorName + ".");
    hide();
}



    void AddCourse::on_Cancel_Push_Button_clicked()
    {
        hide();
    }


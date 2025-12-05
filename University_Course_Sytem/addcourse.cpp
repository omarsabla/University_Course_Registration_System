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
    QString name = ui->nameLE->text().trimmed();
    QString id = ui->idLE->text().trimmed();
    QString creditStr = ui->cdLE->text().trimmed();
    QString enrollmentStr = ui->meLE->text().trimmed();
    QString schedule = ui->stLE->text().trimmed();
    QString department = ui->Department->text().trimmed();
    QString instructorId = ui->instrcutor_ID->text().trimmed();

    
    if (name.isEmpty() || id.isEmpty() || creditStr.isEmpty() || 
        enrollmentStr.isEmpty() || schedule.isEmpty() || department.isEmpty() || instructorId.isEmpty()) {
        QMessageBox::warning(this, "Error", "All fields must be filled out.");
        return;
    }

    
    bool creditOk, enrollmentOk;
    int creditHours = creditStr.toInt(&creditOk);
    int maxEnrollment = enrollmentStr.toInt(&enrollmentOk);

    if (!creditOk || !enrollmentOk || creditHours <= 0 || maxEnrollment <= 0) {
        QMessageBox::warning(this, "Error", "Credit hours and max enrollment must be positive numbers.");
        return;
    }

    
    r.loadcourses();
    for (const auto &course : r.courseList) {
        if (course.id == id) {
            QMessageBox::warning(this, "Error", "A course with this ID already exists.");
            return;
        }
    }

    
    r.loadinstructors();
    
    
    if (r.instructorList.empty()) {
        QMessageBox::warning(this, "Error", "No instructors found in the system. Please add an instructor first.");
        return;
    }
    
    
    bool instructorFound = false;
    int instructorIndex = -1;
    for (size_t i = 0; i < r.instructorList.size(); i++) {
        if (r.instructorList[i].InstructorId.trimmed() == instructorId) {
            instructorIndex = i;
            instructorFound = true;
            break;
        }
    }
    
    if (!instructorFound) {
        
        QString availableIds = "Available Instructor IDs:\n";
        for (const auto &instructor : r.instructorList) {
            availableIds += QString("  - %1 (%2 %3)\n").arg(instructor.InstructorId, instructor.FirstName, instructor.LastName);
        }
        QMessageBox::warning(this, "Error", 
            QString("Instructor with ID '%1' does not exist.\n\n%2").arg(instructorId, availableIds));
        return;
    }

    
    Course newCourse(id, name, instructorId, department, creditHours, schedule, maxEnrollment);
    r.courseList.push_back(newCourse);
    
    
    r.instructorList[instructorIndex].assignedCourses.push_back(id);
    
    
    r.savecourses();
    r.saveinstructors();

    QString instructorName = r.instructorList[instructorIndex].FirstName + " " + r.instructorList[instructorIndex].LastName;
    QMessageBox::information(this, "Success", "Course added successfully and assigned to " + instructorName + ".");
    hide();
}



    void AddCourse::on_Cancel_Push_Button_clicked()
    {
        hide();
    }


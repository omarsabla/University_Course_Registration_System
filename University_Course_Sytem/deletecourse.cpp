#include "deletecourse.h"
#include "ui_deletecourse.h"
#include <fstream>
#include <QMessageBox>
#include "registration_system.h"

DeleteCourse::DeleteCourse(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DeleteCourse)
{
    ui->setupUi(this);
}

DeleteCourse::~DeleteCourse()
{
    delete ui;
}

void DeleteCourse::on_Delete_Push_Button_clicked()
{
    QString id = ui->id_Line_Edit->text();
    
    if (id.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter a course ID.");
        return;
    }
    
    // Load courses from file
    r.loadcourses();
    
    // Find and remove the course with matching ID
    bool found = false;
    for (auto it = r.courseList.begin(); it != r.courseList.end(); ++it) {
        if (it->id == id) {
            r.courseList.erase(it);
            found = true;
            break;
        }
    }
    
    if (found) {
        // Save the updated list
        r.savecourses();
        QMessageBox::information(this, "Success", "Course deleted successfully.");
        hide();
    } else {
        QMessageBox::warning(this, "Error", "Course with this ID not found.");
    }
}

void DeleteCourse::on_Cancel_Push_Button_clicked()
{
    hide();
}


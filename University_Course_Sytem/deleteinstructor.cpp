#include "deleteinstructor.h"
#include "ui_deleteinstructor.h"
#include <iostream>
#include <fstream>
#include <QMessageBox>
#include "registration_system.h"

deleteinstructor::deleteinstructor(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::deleteinstructor)
{
    ui->setupUi(this);
}

deleteinstructor::~deleteinstructor()
{
    delete ui;
}

void deleteinstructor::on_Delete_Push_Button_clicked()
{
    QString id = ui->id_Line_Edit->text();
    
    if (id.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter an instructor ID.");
        return;
    }
    
    // Load instructors from file
    r.loadinstructors();
    
    // Find and remove the instructor with matching ID
    bool found = false;
    for (auto it = r.instructorList.begin(); it != r.instructorList.end(); ++it) {
        if (it->InstructorId == id) {
            r.instructorList.erase(it);
            found = true;
            break;
        }
    }
    
    if (found) {
        // Save the updated list
        r.saveinstructors();
        QMessageBox::information(this, "Success", "Instructor deleted successfully.");
        hide();
    } else {
        QMessageBox::warning(this, "Error", "Instructor with this ID not found.");
    }
}

void deleteinstructor::on_Cancel_Push_Button_clicked()
{
    hide();
}

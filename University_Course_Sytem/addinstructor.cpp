#include "addinstructor.h"
#include "ui_addinstructor.h"
#include <iostream>
#include <fstream>
#include <QMessageBox>
#include "registration_system.h"
#include "instructor.h"

addinstructor::addinstructor(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addinstructor)
{
    ui->setupUi(this);
}

addinstructor::~addinstructor()
{
    delete ui;
}

void addinstructor::on_done_Push_Button_clicked()
{
    QString name, email, id;
    name = ui->name_Line_Edit->text();
    id = ui->id_Line_Edit->text();
    email = ui->email_line_Edit->text();

    QString pass = ui->Password_LineEdit->text();

    bool passmorethan8 = false;
    if(pass.length() >= 8) {
        passmorethan8 = true;
    }

    bool hasNum = false;
    for(int i = 0; i < pass.length(); i++) {
        if(pass[i].isDigit()) {
            hasNum = true;
            break;
        }
    }

    if(!hasNum || !passmorethan8){
        QMessageBox::warning(this, "Error", "Make sure password has at least 8 characters and has a number");
        return;
    }

    if (name.isEmpty() || id.isEmpty() || email.isEmpty() || pass.isEmpty()) {
        QMessageBox::warning(this, "Error", "All fields must be filled out.");
        return;
    }

    Instructor newInstructor(name, email, id, pass);
    r.instructorList.push_back(newInstructor);
    
    // Save all instructors - password map will be automatically created/updated
    r.saveinstructors();
    
    hide();
}

void addinstructor::on_Cancel_Push_Button_clicked()
{
    hide();
}


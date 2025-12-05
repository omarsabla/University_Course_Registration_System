#include "addstudent.h"
#include "ui_addstudent.h"
#include <iostream>
#include <fstream>
#include <QMessageBox>
#include "registration_system.h"
#include "student.h"
using namespace std;

AddStudent::AddStudent(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddStudent)
{
    ui->setupUi(this);
}

AddStudent::~AddStudent()
{
    delete ui;
}

void AddStudent::on_done_Push_Button_clicked()
{
    QString firstName, lastName, email, id;
    firstName = ui -> name_Line_Edit -> text().trimmed();
    lastName = ui -> LastName -> text().trimmed();
    id = ui -> id_Line_Edit -> text().trimmed();
    email = ui -> email_line_Edit -> text().trimmed();

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

        if(!hasNum ||  !passmorethan8){

            QMessageBox::warning(this, "Error", "Make sure password has at least 8 characters and has a number");
            return;
        }

        if (firstName.isEmpty() || lastName.isEmpty() || id.isEmpty() || email.isEmpty() || pass.isEmpty()) {
            QMessageBox::warning(this, "Error", "All fields must be filled out.");
            return;
        }

        Student newStudent(firstName, lastName, email, id, pass);
        r.studentList.push_back(newStudent);
        
        
        r.savestudents();
        
    hide();

}


void AddStudent::on_Cancel_Push_Button_clicked()
{
    hide();
}


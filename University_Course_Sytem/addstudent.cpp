#include "addstudent.h"
#include "ui_addstudent.h"
#include <iostream>
#include <fstream>
#include "registration_system.h"
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
    QString name, email, id;
    std::string n,e,i;
    name = ui -> name_Line_Edit -> text();
    n = name.toStdString();
    id = ui -> id_Line_Edit -> text();
    i = id.toStdString();
    email = ui -> email_line_Edit -> text();
    e = email.toStdString();

    std::ofstream file("/Users/yasser/University_Course_Registration_System/University_Course_Sytem/Students.txt", std::ios::app);
    if (!file.is_open()) {
        qCritical() << "Failed to open file for writing.";
        return;
    }

    file << n << " " << i <<'\n';
    file.close();
    hide();

}


void AddStudent::on_Cancel_Push_Button_clicked()
{
    hide();
}


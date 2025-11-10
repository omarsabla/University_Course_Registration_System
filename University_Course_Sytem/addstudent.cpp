#include "addstudent.h"
#include "ui_addstudent.h"

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

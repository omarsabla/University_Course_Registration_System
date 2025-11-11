#include "admindashboard.h"
#include "ui_admindashboard.h"
#include "addstudent.h"
#include "addcourse.h"
#include "deletestudent.h"
#include "deletecourse.h"
adminDashboard::adminDashboard(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::adminDashboard)
{
    ui->setupUi(this);
}

adminDashboard::~adminDashboard()
{
    delete ui;
}

void adminDashboard::on_add_Student_Button_clicked()
{
    AddStudent* AS = new AddStudent(this);
    AS ->show();
}


void adminDashboard::on_Add_Course_Button_clicked()
{
    AddCourse* AC = new AddCourse(this);
    AC -> show();
}


void adminDashboard::on_Delete_Student_Push_Button_clicked()
{
    DeleteStudent* DS = new DeleteStudent(this);
    DS -> show();
}


void adminDashboard::on_Delete_Course_Button_clicked()
{
    DeleteCourse* DC = new DeleteCourse(this);
    DC ->show();
}




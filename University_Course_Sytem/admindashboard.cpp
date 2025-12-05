#include "admindashboard.h"
#include "ui_admindashboard.h"
#include "addstudent.h"
#include "addcourse.h"
#include "deletestudent.h"
#include "deletecourse.h"
#include "addinstructor.h"
#include "deleteinstructor.h"
#include "liststudents.h"
#include "listcourses.h"
#include "listinstructors.h"
#include "editcourse.h"
#include "reportspage.h"
#include "statisticswindow.h"
#include "registration_system.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

adminDashboard::adminDashboard(const QString &adminEmail, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::adminDashboard)
    , adminEmail(adminEmail)
{
    ui->setupUi(this);
    
    //load data
    r.loadadmins();
    r.loadstudents();
    r.loadcourses();
    r.loadinstructors();
    

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




void adminDashboard::on_Add_Instructor_Button_clicked()
{
    addinstructor* AI = new addinstructor(this);
    AI -> show();
}



void adminDashboard::on_Delete_Instructor_Button_clicked()
{
    deleteinstructor* DI = new deleteinstructor(this);
    DI -> show();
}


void adminDashboard::on_List_Students_Button_clicked()
{
    liststudents* LS = new liststudents(this);
    LS -> show();
}


void adminDashboard::on_List_Courses_Button_clicked()
{
    listcourses* LC = new listcourses(this);
    LC -> show();
}


void adminDashboard::on_List_Instructors_Button_clicked()
{
    listinstructors* LI = new listinstructors(this);
    LI -> show();
}

void adminDashboard::on_Edit_Course_Button_clicked()
{
    EditCourse* EC = new EditCourse(this);
    EC->show();
}

void adminDashboard::on_Reports_Button_clicked()
{
    ReportsPage* RP = new ReportsPage(this);
    RP->show();
}

void adminDashboard::on_Statistics_Button_clicked()
{
    StatisticsWindow* SW = new StatisticsWindow(this);
    SW->show();
}


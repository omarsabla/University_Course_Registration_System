#include "admindashboard.h"
#include "ui_admindashboard.h"
#include "addstudent.h"
#include "addcourse.h"
#include "addinstructor.h"
#include "viewdeletestudent.h"
#include "viewdeletecourse.h"
#include "viewdeleteinstructor.h"
#include "editcourse.h"
#include "editstudent.h"
#include "editinstructor.h"
#include "reportspage.h"
#include "analytics.h"
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
    viewdeletestudent* VDS = new viewdeletestudent(this);
    VDS->show();
}


void adminDashboard::on_Delete_Course_Button_clicked()
{
    viewdeletecourse* VDC = new viewdeletecourse(this);
    VDC->show();
}




void adminDashboard::on_Add_Instructor_Button_clicked()
{
    addinstructor* AI = new addinstructor(this);
    AI -> show();
}



void adminDashboard::on_Delete_Instructor_Button_clicked()
{
    viewdeleteinstructor* VDI = new viewdeleteinstructor(this);
    VDI->show();
}


void adminDashboard::on_List_Students_Button_clicked()
{
    viewdeletestudent* VDS = new viewdeletestudent(this);
    VDS->show();
}


void adminDashboard::on_List_Courses_Button_clicked()
{
    viewdeletecourse* VDC = new viewdeletecourse(this);
    VDC->show();
}


void adminDashboard::on_List_Instructors_Button_clicked()
{
    viewdeleteinstructor* VDI = new viewdeleteinstructor(this);
    VDI->show();
}

void adminDashboard::on_Edit_Course_Button_clicked()
{
    EditCourse* EC = new EditCourse(this);
    EC->show();
}

void adminDashboard::on_Edit_Student_clicked()
{
    EditStudent* ES = new EditStudent(this);
    ES->show();
}

void adminDashboard::on_Edit_Instructors_clicked()
{
    EditInstructor* EI = new EditInstructor(this);
    EI->show();
}

void adminDashboard::on_Reports_Button_clicked()
{
    ReportsPage* RP = new ReportsPage(this);
    RP->show();
}

void adminDashboard::on_Anlytics_clicked()
{
    Analytics* SW = new Analytics(this);
    SW->show();
}


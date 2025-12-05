#include "login_page.h"
#include "ui_login_page.h"
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <QMessageBox>
#include "registration_system.h"
#include "admindashboard.h"
#include "studentwindow.h"
#include "instructorwindow.h"
using namespace std;

LogIn_Page::LogIn_Page(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LogIn_Page)
{

    ui->setupUi(this);


}

LogIn_Page::~LogIn_Page()
{

    delete ui;
}

void LogIn_Page::on_SignIn_Push_Button_clicked()
{
    //load all data using registration system methods
    r.loadadmins();
    r.loadinstructors();
    r.loadstudents();

    QString email, passkey;
    string x, y;
    email = ui->email_Line_Edit->text();
    passkey = ui->password_Line_Edit_2->text();
    x = email.toStdString();
    y = passkey.toStdString();

    auto auth = r.adminPasswords.find(x);
    auto auth2 = r.studentPasswords.find(x);
    auto auth3 = r.instructorPasswords.find(x);
    
    if(auth != r.adminPasswords.end() && y == auth->second) {
        hide();
        adminDashboard* AD1 = new adminDashboard(email, this);
        AD1->show();
    } else if (auth2 != r.studentPasswords.end() && y == auth2->second) {
        hide();
        StudentWindow* SW = new StudentWindow(email, this);
        SW->show();
    } else if (auth3 != r.instructorPasswords.end() && y == auth3->second) {
        hide();
        InstructorWindow* IW = new InstructorWindow(email, this);
        IW->show();
    } else {
        QMessageBox::critical(this, "Error", "Invalid email or password!");
        ui->email_Line_Edit->setText("");
        ui->password_Line_Edit_2->setText("");
    }
}


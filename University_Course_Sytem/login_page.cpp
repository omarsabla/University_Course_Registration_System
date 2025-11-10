#include "login_page.h"
#include "ui_login_page.h"
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <QMessageBox>
#include "registration_system.h"
#include "admindashboard.h"
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
    Registration_System r1;

    ifstream file("/Users/yasser/University_Course_Registration_System/University_Course_Sytem/admins.txt");
    ifstream file2("/Users/yasser/University_Course_Registration_System/University_Course_Sytem/Students.txt");

    if (!file.is_open()) {
        QMessageBox::critical(this, "Error", "File can't be opened!");
        return;
    }
    if (!file2.is_open()) {
        QMessageBox::critical(this, "Error", "File can't be opened!");
        return;
    }

    string username, password;
    while (file >> username >> password) {
        r1.adminPasswords[username] = password;

    }
        string username1, password1;
    while (file2 >> username1 >> password1) {
        r1.studentPasswords[username1] = password1;

    }
    file2.close();
    file.close();

    QString email, passkey;
    string x,y;
    email = ui -> email_Line_Edit -> text();
    passkey = ui -> password_Line_Edit_2 ->text();
    x = email.toStdString();
    y = passkey.toStdString();

    auto auth = r1.adminPasswords.find(x);
    auto auth2 = r1.studentPasswords.find(x);
    if(auth != r1.adminPasswords.end()&& y == auth->second){

        hide();
        adminDashboard* AD1 = new adminDashboard(this);
        AD1  -> show();
    } else if (auth2 != r1.studentPasswords.end()&& y == auth2->second){


    }

    else{
        QMessageBox::critical(this, "Error", "Invalid email or password!");
        ui -> email_Line_Edit-> setText("");
        ui -> password_Line_Edit_2-> setText("");
    }

}


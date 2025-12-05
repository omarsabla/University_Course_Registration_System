#include "deletestudent.h"
#include "ui_deletestudent.h"
#include <iostream>
#include <fstream>
using namespace std;

DeleteStudent::DeleteStudent(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DeleteStudent)
{
    ui->setupUi(this);
}

DeleteStudent::~DeleteStudent()
{
    delete ui;
}

void DeleteStudent::on_Delete_Push_Button_clicked()
{

        QString id = ui->id_Line_Edit->text();
string idStr = id.toStdString();

fstream file("Students.txt", ios::in);
fstream temp("temp.txt", ios::out);

string line;
        while (getline(file, line)) {
            if (line.find(idStr) == string::npos)
                temp << line << '\n';
        }

        file.close();
        temp.close();

remove("Students.txt");
rename("temp.txt", "Students.txt");

        hide();
    }





    void DeleteStudent::on_Cancel_Push_Button_clicked()
    {

        hide();
    }


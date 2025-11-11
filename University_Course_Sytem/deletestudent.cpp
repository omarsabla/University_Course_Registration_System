#include "deletestudent.h"
#include "ui_deletestudent.h"
#include <iostream>
#include <fstream>
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
        std::string idStr = id.toStdString();

        std::fstream file("/Users/yasser/University_Course_Registration_System/University_Course_Sytem/Students.txt", std::ios::in);
        std::fstream temp("/Users/yasser/University_Course_Registration_System/University_Course_Sytem/temp.txt", std::ios::out);

        std::string line;
        while (std::getline(file, line)) {
            if (line.find(idStr) == std::string::npos)
                temp << line << '\n';
        }

        file.close();
        temp.close();

        std::remove("/Users/yasser/University_Course_Registration_System/University_Course_Sytem/Students.txt");
        std::rename("/Users/yasser/University_Course_Registration_System/University_Course_Sytem/temp.txt",
                    "/Users/yasser/University_Course_Registration_System/University_Course_Sytem/Students.txt");

        hide();
    }





    void DeleteStudent::on_Cancel_Push_Button_clicked()
    {

        hide();
    }


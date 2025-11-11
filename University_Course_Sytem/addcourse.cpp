#include "addcourse.h"
#include "ui_addcourse.h"
#include <iostream>
#include <fstream>
AddCourse::AddCourse(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddCourse)
{
    ui->setupUi(this);
}

AddCourse::~AddCourse()
{
    delete ui;
}

void AddCourse::on_done_push_Button_clicked()
{

        QString name, id, credit, enrollment, schedule, instructor;
        std::string n, i, c, e, s, ins;

        name = ui->nameLE->text();
        n = name.toStdString();

        id = ui->idLE->text();
        i = id.toStdString();

        credit = ui-> cdLE ->text();
        c = credit.toStdString();

        enrollment = ui->meLE->text();
        e = enrollment.toStdString();

        schedule = ui->stLE->text();
        s = schedule.toStdString();

        instructor = ui->InstructorLe->text();
        ins = instructor.toStdString();

        std::ofstream file("/Users/yasser/University_Course_Registration_System/University_Course_Sytem/courses.txt", std::ios::app);
        if (!file.is_open()) {
            qCritical() << "Failed to open file for writing.";
            return;
        }

        // Write course data to file
        file << n << " " << i << " " << c << " " << e << " " << s << " " << ins << '\n';
        file.close();

        hide();
    }



    void AddCourse::on_Cancel_Push_Button_clicked()
    {
        hide();
    }


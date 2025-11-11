#include "deletecourse.h"
#include "ui_deletecourse.h"
#include <fstream>
DeleteCourse::DeleteCourse(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DeleteCourse)
{
    ui->setupUi(this);
}

DeleteCourse::~DeleteCourse()
{
    delete ui;
}

void DeleteCourse::on_Delete_Push_Button_clicked()
{
    QString id = ui->id_Line_Edit->text();
    std::string idStr = id.toStdString();

    std::fstream file("/Users/yasser/University_Course_Registration_System/University_Course_Sytem/Courses.txt", std::ios::in);
    std::fstream temp("/Users/yasser/University_Course_Registration_System/University_Course_Sytem/temp.txt", std::ios::out);

    std::string line;
    while (std::getline(file, line)) {
        if (line.find(idStr) == std::string::npos)
            temp << line << '\n';
    }

    file.close();
    temp.close();

    std::remove("/Users/yasser/University_Course_Registration_System/University_Course_Sytem/Courses.txt");
    std::rename("/Users/yasser/University_Course_Registration_System/University_Course_Sytem/temp.txt",
                "/Users/yasser/University_Course_Registration_System/University_Course_Sytem/Courses.txt");

    hide();
}


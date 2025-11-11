#include "viewcourses.h"
#include "ui_viewcourses.h"

viewCourses::viewCourses(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::viewCourses)
{
    ui->setupUi(this);
}

viewCourses::~viewCourses()
{
    delete ui;
}

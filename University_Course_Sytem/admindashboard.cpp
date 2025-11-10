#include "admindashboard.h"
#include "ui_admindashboard.h"

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

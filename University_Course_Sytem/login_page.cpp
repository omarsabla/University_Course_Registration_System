#include "login_page.h"
#include "ui_login_page.h"

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

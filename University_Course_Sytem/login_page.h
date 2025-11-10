#ifndef LOGIN_PAGE_H
#define LOGIN_PAGE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class LogIn_Page;
}
QT_END_NAMESPACE

class LogIn_Page : public QMainWindow
{
    Q_OBJECT

public:
    LogIn_Page(QWidget *parent = nullptr);
    ~LogIn_Page();

private slots:
    void on_SignIn_Push_Button_clicked();

private:
    Ui::LogIn_Page *ui;
};
#endif // LOGIN_PAGE_H

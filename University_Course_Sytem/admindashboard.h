#ifndef ADMINDASHBOARD_H
#define ADMINDASHBOARD_H

#include <QDialog>

namespace Ui {
class adminDashboard;
}

class adminDashboard : public QDialog
{
    Q_OBJECT

public:
    explicit adminDashboard(QWidget *parent = nullptr);
    ~adminDashboard();

private slots:
    void on_add_Student_Button_clicked();

    void on_Add_Course_Button_clicked();


    void on_Delete_Student_Push_Button_clicked();

    void on_Delete_Course_Button_clicked();


private:
    Ui::adminDashboard *ui;
};

#endif // ADMINDASHBOARD_H

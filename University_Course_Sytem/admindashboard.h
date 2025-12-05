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
    explicit adminDashboard(const QString &adminEmail = "", QWidget *parent = nullptr);
    ~adminDashboard();

private slots:
    void on_add_Student_Button_clicked();

    void on_Add_Course_Button_clicked();


    void on_Delete_Student_Push_Button_clicked();

    void on_Delete_Course_Button_clicked();


    void on_Add_Instructor_Button_clicked();

    void on_Delete_Instructor_Button_clicked();

    void on_List_Students_Button_clicked();

    void on_List_Courses_Button_clicked();

    void on_List_Instructors_Button_clicked();
    
    void on_Edit_Course_Button_clicked();
    
    void on_Edit_Student_clicked();
    
    void on_Edit_Instructors_clicked();
    
    void on_Reports_Button_clicked();
    
    void on_Anlytics_clicked();

private:
    Ui::adminDashboard *ui;
    QString adminEmail;
};

#endif // ADMINDASHBOARD_H

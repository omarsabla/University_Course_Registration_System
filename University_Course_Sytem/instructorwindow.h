#ifndef INSTRUCTORWINDOW_H
#define INSTRUCTORWINDOW_H

#include <QDialog>

namespace Ui {
class InstructorWindow;
}

class InstructorWindow : public QDialog
{
    Q_OBJECT

public:
    explicit InstructorWindow(const QString &instructorEmail, QWidget *parent = nullptr);
    ~InstructorWindow();

private slots:
    void on_pushButton_clicked();
    void on_viewcourses_clicked();
    void on_viewenrollment_clicked();

private:
    Ui::InstructorWindow *ui;
    QString instructorEmail;
};

#endif 

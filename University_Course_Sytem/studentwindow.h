#ifndef STUDENTWINDOW_H
#define STUDENTWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "student.h"
#include "course.h"

namespace Ui {
class StudentWindow;
}

class StudentWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StudentWindow(const QString &studentUsername,
                           QWidget *parent = nullptr);
    ~StudentWindow();

private slots:
    void on_registerButton_clicked();

private:
    Ui::StudentWindow *ui;
    Student currentStudent;
    QVector<Course> allCourses;

    void loadCoursesFromFile();
    void fillAvailableCoursesTable();
    void fillMyCoursesTable();
};

#endif

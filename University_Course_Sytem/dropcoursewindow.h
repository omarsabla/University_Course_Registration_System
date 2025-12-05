#ifndef DROPCOURSEWINDOW_H
#define DROPCOURSEWINDOW_H

#include <QDialog>
#include "student.h"

namespace Ui {
class dropcoursewindow;
}

class dropcoursewindow : public QDialog
{
    Q_OBJECT

public:
    explicit dropcoursewindow(const Student &student, QWidget *parent = nullptr);
    ~dropcoursewindow();

private slots:
    void on_Drop_clicked();
    void on_cancel_clicked();

private:
    Ui::dropcoursewindow *ui;
    Student currentStudent;
    void populateRegisteredCoursesTable();
};

#endif // DROPCOURSEWINDOW_H

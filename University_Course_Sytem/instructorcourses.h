#ifndef INSTRUCTORCOURSES_H
#define INSTRUCTORCOURSES_H

#include <QDialog>

namespace Ui {
class instructorcourses;
}

class instructorcourses : public QDialog
{
    Q_OBJECT

public:
    explicit instructorcourses(const QString &instructorEmail, QWidget *parent = nullptr);
    ~instructorcourses();

private slots:
    void on_Done_clicked();

private:
    Ui::instructorcourses *ui;
    QString instructorEmail;
    void populateCoursesTable();
};

#endif 

#ifndef VIEWSCHEDULE_H
#define VIEWSCHEDULE_H

#include <QDialog>
#include "student.h"

namespace Ui {
class viewschedule;
}

class viewschedule : public QDialog
{
    Q_OBJECT

public:
    explicit viewschedule(const Student &student, QWidget *parent = nullptr);
    ~viewschedule();

private slots:
    void on_done_clicked();

private:
    Ui::viewschedule *ui;
    Student currentStudent;
    void populateScheduleTable();
};

#endif // VIEWSCHEDULE_H

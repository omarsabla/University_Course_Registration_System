#ifndef INSTRUCTORSCHEDULE_H
#define INSTRUCTORSCHEDULE_H

#include <QDialog>
#include "instructor.h"

namespace Ui {
class instructorschedule;
}

class instructorschedule : public QDialog
{
    Q_OBJECT

public:
    explicit instructorschedule(const QString &instructorEmail, QWidget *parent = nullptr);
    ~instructorschedule();

private slots:
    void on_done_clicked();

private:
    Ui::instructorschedule *ui;
    QString instructorEmail;
    void populateScheduleTable();
};

#endif // INSTRUCTORSCHEDULE_H

#ifndef VIEWENROLLMENT_H
#define VIEWENROLLMENT_H

#include <QDialog>

namespace Ui {
class viewenrollment;
}

class viewenrollment : public QDialog
{
    Q_OBJECT

public:
    explicit viewenrollment(const QString &instructorEmail, QWidget *parent = nullptr);
    ~viewenrollment();

private slots:
    void on_done_clicked();

    void on_Done_clicked();

private:
    Ui::viewenrollment *ui;
    QString instructorEmail;
    void populateEnrollmentTable();
};

#endif // VIEWENROLLMENT_H

#ifndef REGISTERCOURSE_H
#define REGISTERCOURSE_H

#include <QDialog>
#include "student.h"

namespace Ui {
class registercourse;
}

class registercourse : public QDialog
{
    Q_OBJECT

public:
    explicit registercourse(const Student &student, QWidget *parent = nullptr);
    ~registercourse();

private slots:
    void on_Register_Button_clicked();
    void on_Done_Button_clicked();
    void on_searchLineEdit_textChanged(const QString &text);

private:
    Ui::registercourse *ui;
    Student currentStudent;
    void populateCoursesTable();
    void filterCoursesTable(const QString &searchText);
};

#endif 

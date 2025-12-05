#ifndef EDITCOURSE_H
#define EDITCOURSE_H

#include <QDialog>

namespace Ui {
class EditCourse;
}

class EditCourse : public QDialog
{
    Q_OBJECT

public:
    explicit EditCourse(QWidget *parent = nullptr);
    ~EditCourse();

private slots:
    void on_Select_Button_clicked();
    void on_Save_Button_clicked();
    void on_Cancel_Button_clicked();

private:
    Ui::EditCourse *ui;
    void populateCoursesList();
    QString selectedCourseId;
};

#endif // EDITCOURSE_H


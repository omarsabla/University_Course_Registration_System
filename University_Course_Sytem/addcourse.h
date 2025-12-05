#ifndef ADDCOURSE_H
#define ADDCOURSE_H

#include <QDialog>

namespace Ui {
class AddCourse;
}

class AddCourse : public QDialog
{
    Q_OBJECT

public:
    explicit AddCourse(QWidget *parent = nullptr);
    ~AddCourse();

private slots:
    void on_done_push_Button_clicked();

    void on_Cancel_Push_Button_clicked();

private:
    Ui::AddCourse *ui;
};

#endif 

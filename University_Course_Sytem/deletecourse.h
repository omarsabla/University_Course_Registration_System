#ifndef DELETECOURSE_H
#define DELETECOURSE_H

#include <QDialog>

namespace Ui {
class DeleteCourse;
}

class DeleteCourse : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteCourse(QWidget *parent = nullptr);
    ~DeleteCourse();

private slots:
    void on_Delete_Push_Button_clicked();

private:
    Ui::DeleteCourse *ui;
};

#endif // DELETECOURSE_H

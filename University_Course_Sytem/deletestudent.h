#ifndef DELETESTUDENT_H
#define DELETESTUDENT_H

#include <QDialog>

namespace Ui {
class DeleteStudent;
}

class DeleteStudent : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteStudent(QWidget *parent = nullptr);
    ~DeleteStudent();

private slots:
    void on_Delete_Push_Button_clicked();

    void on_Cancel_Push_Button_clicked();

private:
    Ui::DeleteStudent *ui;
};

#endif // DELETESTUDENT_H

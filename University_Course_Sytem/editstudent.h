#ifndef EDITSTUDENT_H
#define EDITSTUDENT_H

#include <QDialog>

namespace Ui {
class EditStudent;
}

class EditStudent : public QDialog
{
    Q_OBJECT

public:
    explicit EditStudent(QWidget *parent = nullptr);
    ~EditStudent();

private slots:
    void on_Select_Button_clicked();
    void on_Save_Button_clicked();
    void on_Cancel_Button_clicked();

private:
    Ui::EditStudent *ui;
    void populateStudentsList();
    QString selectedStudentId;
};

#endif // EDITSTUDENT_H


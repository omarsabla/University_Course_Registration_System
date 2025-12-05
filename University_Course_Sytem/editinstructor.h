#ifndef EDITINSTRUCTOR_H
#define EDITINSTRUCTOR_H

#include <QDialog>

namespace Ui {
class EditInstructor;
}

class EditInstructor : public QDialog
{
    Q_OBJECT

public:
    explicit EditInstructor(QWidget *parent = nullptr);
    ~EditInstructor();

private slots:
    void on_Select_Button_clicked();
    void on_Save_Button_clicked();
    void on_Cancel_Button_clicked();

private:
    Ui::EditInstructor *ui;
    void populateInstructorsList();
    QString selectedInstructorId;
};

#endif // EDITINSTRUCTOR_H


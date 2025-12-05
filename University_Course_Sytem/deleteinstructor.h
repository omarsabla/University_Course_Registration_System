#ifndef DELETEINSTRUCTOR_H
#define DELETEINSTRUCTOR_H

#include <QDialog>

namespace Ui {
class deleteinstructor;
}

class deleteinstructor : public QDialog
{
    Q_OBJECT

public:
    explicit deleteinstructor(QWidget *parent = nullptr);
    ~deleteinstructor();

private slots:
    void on_Delete_Push_Button_clicked();
    void on_Cancel_Push_Button_clicked();

private:
    Ui::deleteinstructor *ui;
};

#endif // DELETEINSTRUCTOR_H

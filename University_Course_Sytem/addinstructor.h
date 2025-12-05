#ifndef ADDINSTRUCTOR_H
#define ADDINSTRUCTOR_H

#include <QDialog>

namespace Ui {
class addinstructor;
}

class addinstructor : public QDialog
{
    Q_OBJECT

public:
    explicit addinstructor(QWidget *parent = nullptr);
    ~addinstructor();

private slots:
    void on_done_Push_Button_clicked();
    void on_Cancel_Push_Button_clicked();

private:
    Ui::addinstructor *ui;
};

#endif // ADDINSTRUCTOR_H

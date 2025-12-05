#ifndef LISTINSTRUCTORS_H
#define LISTINSTRUCTORS_H

#include <QDialog>

namespace Ui {
class listinstructors;
}

class listinstructors : public QDialog
{
    Q_OBJECT

public:
    explicit listinstructors(QWidget *parent = nullptr);
    ~listinstructors();

private slots:
    void on_Done_Button_clicked();

private:
    Ui::listinstructors *ui;
};

#endif // LISTINSTRUCTORS_H

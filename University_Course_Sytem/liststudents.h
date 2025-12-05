#ifndef LISTSTUDENTS_H
#define LISTSTUDENTS_H

#include <QDialog>

namespace Ui {
class liststudents;
}

class liststudents : public QDialog
{
    Q_OBJECT

public:
    explicit liststudents(QWidget *parent = nullptr);
    ~liststudents();

private slots:
    void on_Done_Button_clicked();

private:
    Ui::liststudents *ui;
};

#endif // LISTSTUDENTS_H

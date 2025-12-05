#ifndef LISTCOURSES_H
#define LISTCOURSES_H

#include <QDialog>

namespace Ui {
class listcourses;
}

class listcourses : public QDialog
{
    Q_OBJECT

public:
    explicit listcourses(QWidget *parent = nullptr);
    ~listcourses();

private slots:
    void on_Done_Button_clicked();

private:
    Ui::listcourses *ui;
};

#endif // LISTCOURSES_H

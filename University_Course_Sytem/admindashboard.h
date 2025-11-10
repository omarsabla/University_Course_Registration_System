#ifndef ADMINDASHBOARD_H
#define ADMINDASHBOARD_H

#include <QDialog>

namespace Ui {
class adminDashboard;
}

class adminDashboard : public QDialog
{
    Q_OBJECT

public:
    explicit adminDashboard(QWidget *parent = nullptr);
    ~adminDashboard();

private:
    Ui::adminDashboard *ui;
};

#endif // ADMINDASHBOARD_H

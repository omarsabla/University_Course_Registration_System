#ifndef STATISTICSWINDOW_H
#define STATISTICSWINDOW_H

#include <QDialog>

namespace Ui {
class StatisticsWindow;
}

class StatisticsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit StatisticsWindow(QWidget *parent = nullptr);
    ~StatisticsWindow();

private slots:
    void on_Done_Button_clicked();

private:
    Ui::StatisticsWindow *ui;
    void updateStatistics();
};

#endif // STATISTICSWINDOW_H


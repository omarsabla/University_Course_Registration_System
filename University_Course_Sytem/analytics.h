#ifndef ANALYTICS_H
#define ANALYTICS_H

#include <QDialog>

namespace Ui {
class Analytics;
}

class Analytics : public QDialog
{
    Q_OBJECT

public:
    explicit Analytics(QWidget *parent = nullptr);
    ~Analytics();

private slots:
    void on_Done_Button_clicked();

private:
    Ui::Analytics *ui;
    void updateStatistics();
    void populatePopularCoursesTable();
    void populateWaitlistTable();
    void populateInstructorMetricsTable();
};

#endif // ANALYTICS_H


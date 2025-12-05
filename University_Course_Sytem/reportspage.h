#ifndef REPORTSPAGE_H
#define REPORTSPAGE_H

#include <QDialog>

namespace Ui {
class ReportsPage;
}

class ReportsPage : public QDialog
{
    Q_OBJECT

public:
    explicit ReportsPage(QWidget *parent = nullptr);
    ~ReportsPage();

private slots:
    void on_StudentSchedules_Button_clicked();
    void on_CourseEnrollment_Button_clicked();
    void on_InstructorWorkload_Button_clicked();
    void on_Export_Button_clicked();
    void on_Done_Button_clicked();

private:
    Ui::ReportsPage *ui;
    QString currentReport;
    void generateStudentSchedulesReport();
    void generateCourseEnrollmentReport();
    void generateInstructorWorkloadReport();
    void exportReport(const QString &format);
};

#endif // REPORTSPAGE_H


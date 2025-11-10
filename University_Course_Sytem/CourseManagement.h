#ifndef COURSEMANAGEMENT_H
#define COURSEMANAGEMENT_H

#include <QWidget>
#include <QVector>
#include "Course.h"

namespace Ui {
class CourseManagement;
}

class CourseManagement : public QWidget {
    Q_OBJECT

public:
    explicit CourseManagement(QWidget *parent = nullptr);
    ~CourseManagement() override;

private:
    Ui::CourseManagement *ui;
    QVector<Course> courses;
    QString filePath = "courses.txt";

    void loadCoursesFromFile();
    void saveCoursesToFile();
    void refreshTable();
    void searchCourses();
    void addCourse();
    void editCourse();
    void deleteCourse();
    void createDefaultCoursesIfMissing();
};

#endif

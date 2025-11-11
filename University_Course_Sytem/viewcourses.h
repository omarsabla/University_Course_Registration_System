#ifndef VIEWCOURSES_H
#define VIEWCOURSES_H

#include <QDialog>

namespace Ui {
class viewCourses;
}

class viewCourses : public QDialog
{
    Q_OBJECT

public:
    explicit viewCourses(QWidget *parent = nullptr);
    ~viewCourses();

private:
    Ui::viewCourses *ui;
};

#endif // VIEWCOURSES_H

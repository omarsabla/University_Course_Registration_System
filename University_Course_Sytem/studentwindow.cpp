#include "studentwindow.h"
#include "ui_studentwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QTableWidgetItem>

StudentWindow::StudentWindow( QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::StudentWindow),
{
    ui->setupUi(this);

    loadCoursesFromFile();
    fillAvailableCoursesTable();
    fillMyCoursesTable();
}

StudentWindow::~StudentWindow()
{
    delete ui;
}

void StudentWindow::loadCoursesFromFile()
{
    allCourses.clear();

    QFile file("courses.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Could not open courses.txt");
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString id, name, time;
        in >> id >> name >> time;
        if (!id.isEmpty() && !name.isEmpty() && !time.isEmpty()) {
            allCourses.append(Course(id, name, time));
        }
    }

    file.close();
}

void StudentWindow::fillAvailableCoursesTable()
{
    ui->availableCoursesTable->clear();
    ui->availableCoursesTable->setRowCount(allCourses.size());
    ui->availableCoursesTable->setColumnCount(3);

    QStringList headers;
    headers << "ID" << "Name" << "Time";
    ui->availableCoursesTable->setHorizontalHeaderLabels(headers);

    for (int i = 0; i < allCourses.size(); ++i) {
        ui->availableCoursesTable->setItem(i, 0,
                                           new QTableWidgetItem(allCourses[i].id));
        ui->availableCoursesTable->setItem(i, 1,
                                           new QTableWidgetItem(allCourses[i].name));
        ui->availableCoursesTable->setItem(i, 2,
                                           new QTableWidgetItem(allCourses[i].timeSlot));
    }
}
/*
void StudentWindow::fillMyCoursesTable()
{
    const auto &v = currentStudent.registered;

    ui->myCoursesTable->clear();
    ui->myCoursesTable->setRowCount((int)v.size());
    ui->myCoursesTable->setColumnCount(3);

    QStringList headers;
    headers << "ID" << "Name" << "Time";
    ui->myCoursesTable->setHorizontalHeaderLabels(headers);

    for (int i = 0; i < (int)v.size(); ++i) {
        ui->myCoursesTable->setItem(i, 0,
                                    new QTableWidgetItem(v[i].id));
        ui->myCoursesTable->setItem(i, 1,
                                    new QTableWidgetItem(v[i].name));
        ui->myCoursesTable->setItem(i, 2,
                                    new QTableWidgetItem(v[i].timeSlot));
    }
}
 */
 /* void StudentWindow::on_registerButton_clicked()
{
    int row = ui->availableCoursesTable->currentRow();

    if (row < 0) {
        QMessageBox::warning(this, "Error", "Please select a course.");
        return;
    }


    Course c = allCourses[row];


    if (currentStudent.alreadyRegistered(c)) {
        QMessageBox::warning(this, "Error", "You are already registered in this course.");
        return;
    }


    if (currentStudent.hasTimeConflict(c)) {
        QMessageBox::warning(this, "Error", "Time conflict with another registered course.");
        return;
    }


    currentStudent.addCourse(c);

    QMessageBox::information(this, "Success", "Course registered.");
    fillMyCoursesTable();
} */

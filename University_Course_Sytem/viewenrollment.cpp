#include "viewenrollment.h"
#include "ui_viewenrollment.h"
#include "registration_system.h"
#include "instructor.h"
#include "course.h"
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QFont>

viewenrollment::viewenrollment(const QString &instructorEmail, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::viewenrollment)
    , instructorEmail(instructorEmail)
{
    ui->setupUi(this);
    populateEnrollmentTable();
}

viewenrollment::~viewenrollment()
{
    delete ui;
}

void viewenrollment::populateEnrollmentTable()
{
    //load instructor and course data
    r.loadinstructors();
    r.loadcourses();

    //find the instructor
    Instructor currentInstructor;
    bool found = false;
    for (const auto &instructor : r.instructorList) {
        if (instructor.Email == instructorEmail) {
            currentInstructor = instructor;
            found = true;
            break;
        }
    }

    if (!found) {
        return;
    }

    QTableWidget *table = ui->tableWidget;
    if (!table) return;

    //clear existing rows
    table->setRowCount(0);

    //set column count - one column per course
    int numCourses = currentInstructor.assignedCourses.size();
    if (numCourses == 0) {
        return;
    }

    table->setColumnCount(numCourses);

    //set headers to course titles
    QStringList headers;
    int col = 0;
    for (const QString &courseId : currentInstructor.assignedCourses) {
        //find the course to get its name
        for (const auto &course : r.courseList) {
            if (course.id == courseId) {
                headers << course.name;  //course title as header
                break;
            }
        }
        col++;
    }
    table->setHorizontalHeaderLabels(headers);

    //find max enrolled students
    int maxStudents = 0;
    for (const QString &courseId : currentInstructor.assignedCourses) {
        for (const auto &course : r.courseList) {
            if (course.id == courseId) {
                int studentCount = course.enrolledStudents.size();
                if (studentCount > maxStudents) {
                    maxStudents = studentCount;
                }
                break;
            }
        }
    }

    //set row count to max students
    table->setRowCount(maxStudents);

    //populate each column with student emails
    col = 0;
    for (const QString &courseId : currentInstructor.assignedCourses) {
        //find the course
        for (const auto &course : r.courseList) {
            if (course.id == courseId) {
                //add student emails to this column
                int row = 0;
                for (const auto &student : course.enrolledStudents) {
                    table->setItem(row, col, new QTableWidgetItem(student.email));

                    //make item non-editable
                    QTableWidgetItem *item = table->item(row, col);
                    if (item) {
                        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                    }

                    row++;
                }
                break;
            }
        }
        col++;
    }

    //formatting options
    table->setAlternatingRowColors(true);
    table->setSelectionBehavior(QAbstractItemView::SelectItems);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setShowGrid(true);

    //style the header
    QHeaderView *header = table->horizontalHeader();
    header->setDefaultSectionSize(200);
    header->setStretchLastSection(false);
    header->setSectionResizeMode(QHeaderView::Interactive);

    QFont headerFont = header->font();
    headerFont.setBold(true);
    headerFont.setPointSize(10);
    header->setFont(headerFont);

    //set column widths
    for (int i = 0; i < numCourses; i++) {
        table->setColumnWidth(i, 200);
    }

    table->resizeColumnsToContents();
    table->verticalHeader()->setDefaultSectionSize(30);
    table->verticalHeader()->setVisible(true);
}

void viewenrollment::on_done_clicked()
{
    hide();
}

void viewenrollment::on_Done_clicked()
{
    hide();
}


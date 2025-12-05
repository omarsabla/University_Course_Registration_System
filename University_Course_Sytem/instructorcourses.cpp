#include "instructorcourses.h"
#include "ui_instructorcourses.h"
#include "registration_system.h"
#include "instructor.h"
#include "course.h"
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QFont>

instructorcourses::instructorcourses(const QString &instructorEmail, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::instructorcourses)
    , instructorEmail(instructorEmail)
{
    ui->setupUi(this);
    populateCoursesTable();
}

instructorcourses::~instructorcourses()
{
    delete ui;
}

void instructorcourses::populateCoursesTable()
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
    
    //set column count and headers
    table->setColumnCount(7);
    QStringList headers;
    headers << "Course ID" << "Course Name" << "Instructor" << "Department"
            << "Credit Hours" << "Time Slot" << "Enrollment";
    table->setHorizontalHeaderLabels(headers);
    
    int row = 0;
    for (const QString &courseId : currentInstructor.assignedCourses) {
        //find the course in courselist
        for (const auto &course : r.courseList) {
            if (course.id == courseId) {
                table->insertRow(row);
                
                //set course id
                table->setItem(row, 0, new QTableWidgetItem(course.id));
                
                //set course name
                table->setItem(row, 1, new QTableWidgetItem(course.name));
                
                //set instructor
                table->setItem(row, 2, new QTableWidgetItem(course.instructor));
                
                //set department
                table->setItem(row, 3, new QTableWidgetItem(course.department));
                
                //set credit hours
                table->setItem(row, 4, new QTableWidgetItem(QString::number(course.creditHours)));
                
                //set time slot
                table->setItem(row, 5, new QTableWidgetItem(course.timeSlot));
                
                //set enrollment
                QString enrollment = QString::number(course.enrolledStudents.size()) + "/" + QString::number(course.maxEnrollment);
                table->setItem(row, 6, new QTableWidgetItem(enrollment));
                
                //make all items non-editable
                for (int j = 0; j < 7; j++) {
                    QTableWidgetItem *item = table->item(row, j);
                    if (item) {
                        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                    }
                }
                
                row++;
                break;
            }
        }
    }
    
    //formatting options
    table->setAlternatingRowColors(true);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setShowGrid(true);
    
    //style the header
    QHeaderView *header = table->horizontalHeader();
    header->setDefaultSectionSize(120);
    header->setStretchLastSection(true);
    header->setSectionResizeMode(QHeaderView::Interactive);
    
    QFont headerFont = header->font();
    headerFont.setBold(true);
    headerFont.setPointSize(10);
    header->setFont(headerFont);
    
    //set column widths
    table->setColumnWidth(0, 100);  //course id
    table->setColumnWidth(1, 180);  //course name
    table->setColumnWidth(2, 120);  //instructor
    table->setColumnWidth(3, 120);  //department
    table->setColumnWidth(4, 100);  //credit hours
    table->setColumnWidth(5, 120);  //time slot
    table->setColumnWidth(6, 100);  //enrollment
    
    table->resizeColumnsToContents();
    table->verticalHeader()->setDefaultSectionSize(30);
    table->verticalHeader()->setVisible(true);
}

void instructorcourses::on_Done_clicked()
{
    hide();
}


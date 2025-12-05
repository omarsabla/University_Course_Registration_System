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
    
    r.loadinstructors();
    r.loadcourses();
    
    
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
    
    
    table->setRowCount(0);
    
    
    table->setColumnCount(7);
    QStringList headers;
    headers << "Course ID" << "Course Name" << "Instructor" << "Department"
            << "Credit Hours" << "Time Slot" << "Enrollment";
    table->setHorizontalHeaderLabels(headers);
    
    int row = 0;
    for (const QString &courseId : currentInstructor.assignedCourses) {
        
        for (const auto &course : r.courseList) {
            if (course.id == courseId) {
                table->insertRow(row);
                
                
                table->setItem(row, 0, new QTableWidgetItem(course.id));
                
                
                table->setItem(row, 1, new QTableWidgetItem(course.name));
                
                
                table->setItem(row, 2, new QTableWidgetItem(r.getInstructorName(course.instructorId)));
                
                
                table->setItem(row, 3, new QTableWidgetItem(course.department));
                
                
                table->setItem(row, 4, new QTableWidgetItem(QString::number(course.creditHours)));
                
                
                table->setItem(row, 5, new QTableWidgetItem(course.timeSlot));
                
                
                QString enrollment = QString::number(course.enrolledStudents.size()) + "/" + QString::number(course.maxEnrollment);
                table->setItem(row, 6, new QTableWidgetItem(enrollment));
                
                
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
    
    
    table->setAlternatingRowColors(true);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setShowGrid(true);
    
    
    QHeaderView *header = table->horizontalHeader();
    header->setDefaultSectionSize(120);
    header->setStretchLastSection(true);
    header->setSectionResizeMode(QHeaderView::Interactive);
    
    QFont headerFont = header->font();
    headerFont.setBold(true);
    headerFont.setPointSize(10);
    header->setFont(headerFont);
    
    
    table->setColumnWidth(0, 100);  
    table->setColumnWidth(1, 180);  
    table->setColumnWidth(2, 120);  
    table->setColumnWidth(3, 120);  
    table->setColumnWidth(4, 100);  
    table->setColumnWidth(5, 120);  
    table->setColumnWidth(6, 100);  
    
    table->resizeColumnsToContents();
    table->verticalHeader()->setDefaultSectionSize(30);
    table->verticalHeader()->setVisible(true);
}

void instructorcourses::on_Done_clicked()
{
    hide();
}


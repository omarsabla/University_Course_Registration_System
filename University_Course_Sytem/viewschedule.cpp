#include "viewschedule.h"
#include "ui_viewschedule.h"
#include "registration_system.h"
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QFont>
#include <vector>

viewschedule::viewschedule(const Student &student, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::viewschedule)
    , currentStudent(student)
{
    ui->setupUi(this);
    populateScheduleTable();
}

viewschedule::~viewschedule()
{
    delete ui;
}

void viewschedule::populateScheduleTable()
{
    //reload student data
    r.loadstudents();
    r.loadcourses();
    
    //find and update student
    for (const auto &student : r.studentList) {
        if (student.id == currentStudent.id) {
            currentStudent = student;
            break;
        }
    }
    
    //setup table
    QTableWidget *table = ui->tableWidget;
    
    //clear existing items
    table->clear();
    table->setRowCount(0);
    
    //set column count and headers
    table->setColumnCount(3);
    QStringList headers;
    headers << "Time Slot" << "Course ID" << "Course Name";
    table->setHorizontalHeaderLabels(headers);
    
    //get registered courses and sort by time slot
    std::vector<Course> courses = currentStudent.registered;
    
    //sort courses by time slot using bubble sort
    for (size_t i = 0; i < courses.size(); ++i) {
        for (size_t j = 0; j < courses.size() - 1 - i; ++j) {
            if (courses[j].timeSlot > courses[j + 1].timeSlot) {
                //swap courses
                Course temp = courses[j];
                courses[j] = courses[j + 1];
                courses[j + 1] = temp;
            }
        }
    }
    
    //set row count
    int courseCount = courses.size();
    table->setRowCount(courseCount);
    
    if (courseCount == 0) {
        return;
    }
    
    //populate table with sorted courses
    for (int i = 0; i < courseCount; ++i) {
        const Course &course = courses[i];
        
        //set time slot
        table->setItem(i, 0, new QTableWidgetItem(course.timeSlot));
        
        //set course id
        table->setItem(i, 1, new QTableWidgetItem(course.id));
        
        //set course name
        table->setItem(i, 2, new QTableWidgetItem(course.name));
        
        //make all items non-editable
        for (int j = 0; j < 3; j++) {
            QTableWidgetItem *item = table->item(i, j);
            if (item) {
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            }
        }
    }
    
    //formatting options
    table->setAlternatingRowColors(true);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setShowGrid(true);
    table->setSortingEnabled(false); //disable sorting since we manually sorted
    
    //style the header
    QHeaderView *header = table->horizontalHeader();
    header->setDefaultSectionSize(150);
    header->setStretchLastSection(true);
    header->setSectionResizeMode(QHeaderView::Interactive);
    
    QFont headerFont = header->font();
    headerFont.setBold(true);
    headerFont.setPointSize(10);
    header->setFont(headerFont);
    
    //set column widths
    table->setColumnWidth(0, 150);  //time slot
    table->setColumnWidth(1, 120);  //course id
    table->setColumnWidth(2, 300);  //course name
    
    table->resizeColumnsToContents();
    table->verticalHeader()->setDefaultSectionSize(30);
    table->verticalHeader()->setVisible(true);
    table->setVisible(true);
    table->show();
}

void viewschedule::on_done_clicked()
{
    hide();
}


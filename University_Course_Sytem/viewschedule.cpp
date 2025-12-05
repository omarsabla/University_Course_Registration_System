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
    
    r.loadstudents();
    r.loadcourses();
    
    
    for (const auto &student : r.studentList) {
        if (student.id == currentStudent.id) {
            currentStudent = student;
            break;
        }
    }
    
    
    QTableWidget *table = ui->tableWidget;
    
    
    table->clear();
    table->setRowCount(0);
    
    
    table->setColumnCount(3);
    QStringList headers;
    headers << "Time Slot" << "Course ID" << "Course Name";
    table->setHorizontalHeaderLabels(headers);
    
    
    std::vector<Course> courses = currentStudent.registered;
    
    
    for (size_t i = 0; i < courses.size(); ++i) {
        for (size_t j = 0; j < courses.size() - 1 - i; ++j) {
            if (courses[j].timeSlot > courses[j + 1].timeSlot) {
                
                Course temp = courses[j];
                courses[j] = courses[j + 1];
                courses[j + 1] = temp;
            }
        }
    }
    
    
    int courseCount = courses.size();
    table->setRowCount(courseCount);
    
    if (courseCount == 0) {
        return;
    }
    
    
    for (int i = 0; i < courseCount; ++i) {
        const Course &course = courses[i];
        
        
        table->setItem(i, 0, new QTableWidgetItem(course.timeSlot));
        
        
        table->setItem(i, 1, new QTableWidgetItem(course.id));
        
        
        table->setItem(i, 2, new QTableWidgetItem(course.name));
        
        
        for (int j = 0; j < 3; j++) {
            QTableWidgetItem *item = table->item(i, j);
            if (item) {
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            }
        }
    }
    
    
    table->setAlternatingRowColors(true);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setShowGrid(true);
    table->setSortingEnabled(false); 
    
    
    QHeaderView *header = table->horizontalHeader();
    header->setDefaultSectionSize(150);
    header->setStretchLastSection(true);
    header->setSectionResizeMode(QHeaderView::Interactive);
    
    QFont headerFont = header->font();
    headerFont.setBold(true);
    headerFont.setPointSize(10);
    header->setFont(headerFont);
    
    
    table->setColumnWidth(0, 150);  
    table->setColumnWidth(1, 120);  
    table->setColumnWidth(2, 300);  
    
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


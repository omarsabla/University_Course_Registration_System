#include "listcourses.h"
#include "ui_listcourses.h"
#include "registration_system.h"
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QFont>

listcourses::listcourses(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::listcourses)
{
    ui->setupUi(this);
    
    // Load courses from registration system
    r.loadcourses();
    
    // Set up the table
    QTableWidget *table = ui->tableWidget;
    
    // Set column count and headers
    table->setColumnCount(7);
    QStringList headers;
    headers << "Course ID" << "Course Name" << "Instructor" << "Department" 
            << "Credit Hours" << "Time Slot" << "Max Enrollment";
    table->setHorizontalHeaderLabels(headers);
    
    // Set row count based on number of courses
    table->setRowCount(r.courseList.size());
    
    // Populate the table with course data
    for (int i = 0; i < r.courseList.size(); ++i) {
        const Course &course = r.courseList[i];
        
        // Set Course ID
        table->setItem(i, 0, new QTableWidgetItem(course.id));
        
        // Set Course Name
        table->setItem(i, 1, new QTableWidgetItem(course.name));
        
        // Set Instructor
        table->setItem(i, 2, new QTableWidgetItem(course.instructor));
        
        // Set Department
        table->setItem(i, 3, new QTableWidgetItem(course.department));
        
        // Set Credit Hours
        table->setItem(i, 4, new QTableWidgetItem(QString::number(course.creditHours)));
        
        // Set Time Slot
        table->setItem(i, 5, new QTableWidgetItem(course.timeSlot));
        
        // Set Max Enrollment
        table->setItem(i, 6, new QTableWidgetItem(QString::number(course.maxEnrollment)));
        
        // Make all items non-editable
        for (int j = 0; j < 7; j++) {
            QTableWidgetItem *item = table->item(i, j);
            if (item) {
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            }
        }
    }
    
    // Formatting options
    table->setAlternatingRowColors(true);  // Alternating row colors
    table->setSelectionBehavior(QAbstractItemView::SelectRows);  // Select entire rows
    table->setSelectionMode(QAbstractItemView::SingleSelection);  // Single selection
    table->setShowGrid(true);  // Show grid lines
    table->setSortingEnabled(true);  // Enable sorting
    
    // Style the header
    QHeaderView *header = table->horizontalHeader();
    header->setDefaultSectionSize(120);  // Default column width
    header->setStretchLastSection(false);  // Don't stretch last column
    header->setSectionResizeMode(QHeaderView::Interactive);  // Allow manual resizing
    
    // Set font for header
    QFont headerFont = header->font();
    headerFont.setBold(true);
    headerFont.setPointSize(10);
    header->setFont(headerFont);
    
    // Set column widths
    table->setColumnWidth(0, 100);  // Course ID
    table->setColumnWidth(1, 180);  // Course Name
    table->setColumnWidth(2, 120);  // Instructor
    table->setColumnWidth(3, 120);  // Department
    table->setColumnWidth(4, 100);  // Credit Hours
    table->setColumnWidth(5, 120);  // Time Slot
    table->setColumnWidth(6, 120);  // Max Enrollment
    
    // Resize columns to fit content initially
    table->resizeColumnsToContents();
    
    // Set row height
    table->verticalHeader()->setDefaultSectionSize(30);
    table->verticalHeader()->setVisible(true);
}

listcourses::~listcourses()
{
    delete ui;
}

void listcourses::on_Done_Button_clicked()
{
    hide();
}


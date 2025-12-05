#include "listinstructors.h"
#include "ui_listinstructors.h"
#include "registration_system.h"
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QFont>

listinstructors::listinstructors(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::listinstructors)
{
    ui->setupUi(this);
    
    // Load instructors from registration system
    r.loadinstructors();
    
    // Set up the table - using tableWidget like listcourses
    QTableWidget *table = ui->tableWidget;
    
    // Set column count and headers
    table->setColumnCount(3);
    QStringList headers;
    headers << "Instructor ID" << "Name" << "Email";
    table->setHorizontalHeaderLabels(headers);
    
    // Set row count based on number of instructors
    table->setRowCount(r.instructorList.size());
    
    // Populate the table with instructor data
    for (int i = 0; i < r.instructorList.size(); ++i) {
        const Instructor &instructor = r.instructorList[i];
        
        // Set Instructor ID
        table->setItem(i, 0, new QTableWidgetItem(instructor.InstructorId));
        
        // Set Name
        table->setItem(i, 1, new QTableWidgetItem(instructor.Name));
        
        // Set Email
        table->setItem(i, 2, new QTableWidgetItem(instructor.Email));
        
        // Make all items non-editable
        for (int j = 0; j < 3; j++) {
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
    header->setDefaultSectionSize(200);  // Default column width
    header->setStretchLastSection(true);  // Stretch last column
    header->setSectionResizeMode(QHeaderView::Interactive);  // Allow manual resizing
    
    // Set font for header
    QFont headerFont = header->font();
    headerFont.setBold(true);
    headerFont.setPointSize(10);
    header->setFont(headerFont);
    
    // Set column widths
    table->setColumnWidth(0, 150);  // Instructor ID
    table->setColumnWidth(1, 200);  // Name
    table->setColumnWidth(2, 250);  // Email
    
    // Resize columns to fit content initially
    table->resizeColumnsToContents();
    
    // Set row height
    table->verticalHeader()->setDefaultSectionSize(30);
    table->verticalHeader()->setVisible(true);
}

listinstructors::~listinstructors()
{
    delete ui;
}

void listinstructors::on_Done_Button_clicked()
{
    hide();
}


#include "liststudents.h"
#include "ui_liststudents.h"
#include "registration_system.h"
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QFont>

liststudents::liststudents(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::liststudents)
{
    ui->setupUi(this);
    
    // Load students from registration system
    r.loadstudents();
    
    // Create a model for the table view
    QStandardItemModel *model = new QStandardItemModel(this);
    
    // Set headers with bold font - now includes email
    model->setHorizontalHeaderLabels(QStringList() << "Student Name" << "Student ID" << "Email");
    
    // Populate the table with student data
    for (const auto &student : r.studentList) {
        QList<QStandardItem*> row;
        QStandardItem *nameItem = new QStandardItem(student.name);
        QStandardItem *idItem = new QStandardItem(student.id);
        QStandardItem *emailItem = new QStandardItem(student.email);
        
        // Make items non-editable
        nameItem->setEditable(false);
        idItem->setEditable(false);
        emailItem->setEditable(false);
        
        row << nameItem << idItem << emailItem;
        model->appendRow(row);
    }
    
    // Set the model to the table view
    ui->tableView->setModel(model);
    
    // Formatting options
    ui->tableView->setAlternatingRowColors(true);  // Alternating row colors
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);  // Select entire rows
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);  // Single selection
    ui->tableView->setShowGrid(true);  // Show grid lines
    ui->tableView->setSortingEnabled(true);  // Enable sorting
    
    // Style the header
    QHeaderView *header = ui->tableView->horizontalHeader();
    header->setDefaultSectionSize(200);  // Default column width
    header->setStretchLastSection(true);  // Stretch last column
    header->setSectionResizeMode(QHeaderView::Interactive);  // Allow manual resizing
    
    // Set font for header
    QFont headerFont = header->font();
    headerFont.setBold(true);
    headerFont.setPointSize(10);
    header->setFont(headerFont);
    
    // Resize columns to fit content initially
    ui->tableView->resizeColumnsToContents();
    
    // Set minimum column widths
    ui->tableView->setColumnWidth(0, 200);  // Name column
    ui->tableView->setColumnWidth(1, 150);  // ID column
    ui->tableView->setColumnWidth(2, 250);  // Email column
    
    // Set row height
    ui->tableView->verticalHeader()->setDefaultSectionSize(30);
    ui->tableView->verticalHeader()->setVisible(true);
}

liststudents::~liststudents()
{
    delete ui;
}

void liststudents::on_Done_Button_clicked()
{
    hide();
}


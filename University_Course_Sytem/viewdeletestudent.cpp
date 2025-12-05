#include "viewdeletestudent.h"
#include "ui_viewdeletestudent.h"
#include "registration_system.h"
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QFont>
#include <QMessageBox>

viewdeletestudent::viewdeletestudent(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::viewdeletestudent)
{
    ui->setupUi(this);
    populateTable();
    
    //connect search line edit
    connect(ui->searchLineEdit, &QLineEdit::textChanged, this, &viewdeletestudent::on_searchLineEdit_textChanged);
    
    //auto-fill id when row is selected
    connect(ui->tableWidget, &QTableWidget::itemSelectionChanged, this, [this]() {
        QList<QTableWidgetItem*> selected = ui->tableWidget->selectedItems();
        if (!selected.isEmpty()) {
            int row = selected.first()->row();
            QTableWidgetItem *idItem = ui->tableWidget->item(row, 1); //id is in column 1
            if (idItem) {
                ui->idLineEdit->setText(idItem->text());
            }
        }
    });
}

viewdeletestudent::~viewdeletestudent()
{
    delete ui;
}

void viewdeletestudent::populateTable()
{
    //load students
    r.loadstudents();
    
    QTableWidget *table = ui->tableWidget;
    
    //set column count and headers
    table->setColumnCount(3);
    QStringList headers;
    headers << "Student Name" << "Student ID" << "Email";
    table->setHorizontalHeaderLabels(headers);
    
    //set row count
    table->setRowCount(r.studentList.size());
    
    //populate table
    for (int i = 0; i < r.studentList.size(); ++i) {
        const Student &student = r.studentList[i];
        
        table->setItem(i, 0, new QTableWidgetItem(student.name));
        table->setItem(i, 1, new QTableWidgetItem(student.id));
        table->setItem(i, 2, new QTableWidgetItem(student.email));
        
        //make items non-editable
        for (int j = 0; j < 3; j++) {
            QTableWidgetItem *item = table->item(i, j);
            if (item) {
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            }
        }
    }
    
    //formatting
    table->setAlternatingRowColors(true);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setShowGrid(true);
    table->setSortingEnabled(true);
    
    //style header
    QHeaderView *header = table->horizontalHeader();
    header->setDefaultSectionSize(200);
    header->setStretchLastSection(true);
    header->setSectionResizeMode(QHeaderView::Interactive);
    
    QFont headerFont = header->font();
    headerFont.setBold(true);
    headerFont.setPointSize(10);
    header->setFont(headerFont);
    
    //set column widths
    table->setColumnWidth(0, 200);
    table->setColumnWidth(1, 150);
    table->setColumnWidth(2, 250);
    
    table->resizeColumnsToContents();
    table->verticalHeader()->setDefaultSectionSize(30);
    table->verticalHeader()->setVisible(true);
}

void viewdeletestudent::on_searchLineEdit_textChanged(const QString &arg1)
{
    filterTable(arg1);
}

void viewdeletestudent::filterTable(const QString &searchText)
{
    QTableWidget *table = ui->tableWidget;
    
    for (int i = 0; i < table->rowCount(); ++i) {
        bool match = false;
        
        if (searchText.isEmpty()) {
            match = true;
        } else {
            //check all columns for match
            for (int j = 0; j < table->columnCount(); ++j) {
                QTableWidgetItem *item = table->item(i, j);
                if (item && item->text().contains(searchText, Qt::CaseInsensitive)) {
                    match = true;
                    break;
                }
            }
        }
        
        table->setRowHidden(i, !match);
    }
}

void viewdeletestudent::on_Delete_Button_clicked()
{
    QString id = ui->idLineEdit->text();
    
    if (id.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter a student ID.");
        return;
    }
    
    //reload students
    r.loadstudents();
    
    //find and remove student
    bool found = false;
    for (auto it = r.studentList.begin(); it != r.studentList.end(); ++it) {
        if (it->id == id) {
            r.studentList.erase(it);
            found = true;
            break;
        }
    }
    
    if (found) {
        //save changes
        r.savestudents();
        QMessageBox::information(this, "Success", "Student deleted successfully.");
        
        //refresh table
        populateTable();
        ui->idLineEdit->clear();
    } else {
        QMessageBox::warning(this, "Error", "Student with this ID not found.");
    }
}

void viewdeletestudent::on_Done_Button_clicked()
{
    hide();
}


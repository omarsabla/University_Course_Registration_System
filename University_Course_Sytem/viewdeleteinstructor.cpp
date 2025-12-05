#include "viewdeleteinstructor.h"
#include "ui_viewdeleteinstructor.h"
#include "registration_system.h"
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QFont>
#include <QMessageBox>

viewdeleteinstructor::viewdeleteinstructor(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::viewdeleteinstructor)
{
    ui->setupUi(this);
    populateTable();
    
    
    connect(ui->searchLineEdit, &QLineEdit::textChanged, this, &viewdeleteinstructor::on_searchLineEdit_textChanged);
    
    
    connect(ui->tableWidget, &QTableWidget::itemSelectionChanged, this, [this]() {
        QList<QTableWidgetItem*> selected = ui->tableWidget->selectedItems();
        if (!selected.isEmpty()) {
            int row = selected.first()->row();
            QTableWidgetItem *idItem = ui->tableWidget->item(row, 0); 
            if (idItem) {
                ui->idLineEdit->setText(idItem->text());
            }
        }
    });
}

viewdeleteinstructor::~viewdeleteinstructor()
{
    delete ui;
}

void viewdeleteinstructor::populateTable()
{
    
    r.loadinstructors();
    
    QTableWidget *table = ui->tableWidget;
    
    
    table->setColumnCount(5);
    QStringList headers;
    headers << "Instructor ID" << "First Name" << "Last Name" << "Email" << "Password";
    table->setHorizontalHeaderLabels(headers);
    
    
    table->setRowCount(r.instructorList.size());
    
    
    for (int i = 0; i < r.instructorList.size(); ++i) {
        const Instructor &instructor = r.instructorList[i];
        
        table->setItem(i, 0, new QTableWidgetItem(instructor.InstructorId));
        table->setItem(i, 1, new QTableWidgetItem(instructor.FirstName));
        table->setItem(i, 2, new QTableWidgetItem(instructor.LastName));
        table->setItem(i, 3, new QTableWidgetItem(instructor.Email));
        table->setItem(i, 4, new QTableWidgetItem(instructor.instructorPassword));
        
        
        for (int j = 0; j < 5; j++) {
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
    table->setSortingEnabled(true);
    
    
    QHeaderView *header = table->horizontalHeader();
    header->setDefaultSectionSize(200);
    header->setStretchLastSection(true);
    header->setSectionResizeMode(QHeaderView::Interactive);
    
    QFont headerFont = header->font();
    headerFont.setBold(true);
    headerFont.setPointSize(10);
    header->setFont(headerFont);
    
    
    table->setColumnWidth(0, 150);
    table->setColumnWidth(1, 200);
    table->setColumnWidth(2, 250);
    table->setColumnWidth(3, 150);
    
    table->resizeColumnsToContents();
    table->verticalHeader()->setDefaultSectionSize(30);
    table->verticalHeader()->setVisible(true);
}

void viewdeleteinstructor::on_searchLineEdit_textChanged(const QString &arg1)
{
    filterTable(arg1);
}

void viewdeleteinstructor::filterTable(const QString &searchText)
{
    QTableWidget *table = ui->tableWidget;
    
    for (int i = 0; i < table->rowCount(); ++i) {
        bool match = false;
        
        if (searchText.isEmpty()) {
            match = true;
        } else {
            
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

void viewdeleteinstructor::on_Delete_Button_clicked()
{
    QString id = ui->idLineEdit->text();
    
    if (id.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter an instructor ID.");
        return;
    }
    
    
    r.loadinstructors();
    
    
    bool found = false;
    for (auto it = r.instructorList.begin(); it != r.instructorList.end(); ++it) {
        if (it->InstructorId == id) {
            r.instructorList.erase(it);
            found = true;
            break;
        }
    }
    
    if (found) {
        
        r.saveinstructors();
        QMessageBox::information(this, "Success", "Instructor deleted successfully.");
        
        
        populateTable();
        ui->idLineEdit->clear();
    } else {
        QMessageBox::warning(this, "Error", "Instructor with this ID not found.");
    }
}

void viewdeleteinstructor::on_Done_Button_clicked()
{
    hide();
}


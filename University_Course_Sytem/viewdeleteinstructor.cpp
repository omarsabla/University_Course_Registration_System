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
    
    //connect search line edit
    connect(ui->searchLineEdit, &QLineEdit::textChanged, this, &viewdeleteinstructor::on_searchLineEdit_textChanged);
    
    //auto-fill id when row is selected
    connect(ui->tableWidget, &QTableWidget::itemSelectionChanged, this, [this]() {
        QList<QTableWidgetItem*> selected = ui->tableWidget->selectedItems();
        if (!selected.isEmpty()) {
            int row = selected.first()->row();
            QTableWidgetItem *idItem = ui->tableWidget->item(row, 0); //id is in column 0
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
    //load instructors
    r.loadinstructors();
    
    QTableWidget *table = ui->tableWidget;
    
    //set column count and headers
    table->setColumnCount(3);
    QStringList headers;
    headers << "Instructor ID" << "Name" << "Email";
    table->setHorizontalHeaderLabels(headers);
    
    //set row count
    table->setRowCount(r.instructorList.size());
    
    //populate table
    for (int i = 0; i < r.instructorList.size(); ++i) {
        const Instructor &instructor = r.instructorList[i];
        
        table->setItem(i, 0, new QTableWidgetItem(instructor.InstructorId));
        table->setItem(i, 1, new QTableWidgetItem(instructor.Name));
        table->setItem(i, 2, new QTableWidgetItem(instructor.Email));
        
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
    table->setColumnWidth(0, 150);
    table->setColumnWidth(1, 200);
    table->setColumnWidth(2, 250);
    
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

void viewdeleteinstructor::on_Delete_Button_clicked()
{
    QString id = ui->idLineEdit->text();
    
    if (id.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter an instructor ID.");
        return;
    }
    
    //reload instructors
    r.loadinstructors();
    
    //find and remove instructor
    bool found = false;
    for (auto it = r.instructorList.begin(); it != r.instructorList.end(); ++it) {
        if (it->InstructorId == id) {
            r.instructorList.erase(it);
            found = true;
            break;
        }
    }
    
    if (found) {
        //save changes
        r.saveinstructors();
        QMessageBox::information(this, "Success", "Instructor deleted successfully.");
        
        //refresh table
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


#include "viewdeletecourse.h"
#include "ui_viewdeletecourse.h"
#include "registration_system.h"
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QFont>
#include <QMessageBox>

viewdeletecourse::viewdeletecourse(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::viewdeletecourse)
{
    ui->setupUi(this);
    populateTable();
    
    //connect search line edit
    connect(ui->searchLineEdit, &QLineEdit::textChanged, this, &viewdeletecourse::on_searchLineEdit_textChanged);
    
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

viewdeletecourse::~viewdeletecourse()
{
    delete ui;
}

void viewdeletecourse::populateTable()
{
    //load courses
    r.loadcourses();
    
    QTableWidget *table = ui->tableWidget;
    
    //set column count and headers
    table->setColumnCount(7);
    QStringList headers;
    headers << "Course ID" << "Course Name" << "Instructor" << "Department" 
            << "Credit Hours" << "Time Slot" << "Max Enrollment";
    table->setHorizontalHeaderLabels(headers);
    
    //set row count
    table->setRowCount(r.courseList.size());
    
    //populate table
    for (int i = 0; i < r.courseList.size(); ++i) {
        const Course &course = r.courseList[i];
        
        table->setItem(i, 0, new QTableWidgetItem(course.id));
        table->setItem(i, 1, new QTableWidgetItem(course.name));
        table->setItem(i, 2, new QTableWidgetItem(course.instructor));
        table->setItem(i, 3, new QTableWidgetItem(course.department));
        table->setItem(i, 4, new QTableWidgetItem(QString::number(course.creditHours)));
        table->setItem(i, 5, new QTableWidgetItem(course.timeSlot));
        table->setItem(i, 6, new QTableWidgetItem(QString::number(course.maxEnrollment)));
        
        //make items non-editable
        for (int j = 0; j < 7; j++) {
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
    header->setDefaultSectionSize(120);
    header->setStretchLastSection(false);
    header->setSectionResizeMode(QHeaderView::Interactive);
    
    QFont headerFont = header->font();
    headerFont.setBold(true);
    headerFont.setPointSize(10);
    header->setFont(headerFont);
    
    //set column widths
    table->setColumnWidth(0, 100);
    table->setColumnWidth(1, 180);
    table->setColumnWidth(2, 120);
    table->setColumnWidth(3, 120);
    table->setColumnWidth(4, 100);
    table->setColumnWidth(5, 120);
    table->setColumnWidth(6, 120);
    
    table->resizeColumnsToContents();
    table->verticalHeader()->setDefaultSectionSize(30);
    table->verticalHeader()->setVisible(true);
}

void viewdeletecourse::on_searchLineEdit_textChanged(const QString &arg1)
{
    filterTable(arg1);
}

void viewdeletecourse::filterTable(const QString &searchText)
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

void viewdeletecourse::on_Delete_Button_clicked()
{
    QString id = ui->idLineEdit->text();
    
    if (id.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter a course ID.");
        return;
    }
    
    //reload courses
    r.loadcourses();
    
    //find and remove course
    bool found = false;
    for (auto it = r.courseList.begin(); it != r.courseList.end(); ++it) {
        if (it->id == id) {
            r.courseList.erase(it);
            found = true;
            break;
        }
    }
    
    if (found) {
        //save changes
        r.savecourses();
        QMessageBox::information(this, "Success", "Course deleted successfully.");
        
        //refresh table
        populateTable();
        ui->idLineEdit->clear();
    } else {
        QMessageBox::warning(this, "Error", "Course with this ID not found.");
    }
}

void viewdeletecourse::on_Done_Button_clicked()
{
    hide();
}


#include "editstudent.h"
#include "ui_editstudent.h"
#include "registration_system.h"
#include <QMessageBox>
#include <QTableWidgetItem>

EditStudent::EditStudent(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditStudent)
    , selectedStudentId("")
{
    ui->setupUi(this);
    populateStudentsList();
}

EditStudent::~EditStudent()
{
    delete ui;
}

void EditStudent::populateStudentsList()
{
    r.loadstudents();
    
    QTableWidget *table = ui->tableWidget;
    table->setColumnCount(5);
    QStringList headers;
    headers << "Student ID" << "First Name" << "Last Name" << "Email" << "Password";
    table->setHorizontalHeaderLabels(headers);
    
    table->setRowCount(r.studentList.size());
    
    for (int i = 0; i < r.studentList.size(); ++i) {
        const Student &student = r.studentList[i];
        table->setItem(i, 0, new QTableWidgetItem(student.id));
        table->setItem(i, 1, new QTableWidgetItem(student.firstName));
        table->setItem(i, 2, new QTableWidgetItem(student.lastName));
        table->setItem(i, 3, new QTableWidgetItem(student.email));
        table->setItem(i, 4, new QTableWidgetItem(student.password));
        
        for (int j = 0; j < 5; j++) {
            QTableWidgetItem *item = table->item(i, j);
            if (item) {
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            }
        }
    }
    
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->resizeColumnsToContents();
}

void EditStudent::on_Select_Button_clicked()
{
    int currentRow = ui->tableWidget->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Error", "Please select a student from the table.");
        return;
    }
    
    QTableWidgetItem *idItem = ui->tableWidget->item(currentRow, 0);
    if (!idItem) {
        QMessageBox::warning(this, "Error", "Invalid selection.");
        return;
    }
    
    selectedStudentId = idItem->text();
    
    
    r.loadstudents();
    for (const auto &student : r.studentList) {
        if (student.id == selectedStudentId) {
            ui->idLineEdit->setText(student.id);
            ui->nameLineEdit->setText(student.firstName);
            ui->LastName->setText(student.lastName);
            ui->emailLineEdit->setText(student.email);
            ui->passwordLineEdit->setText(student.password);
            break;
        }
    }
}

void EditStudent::on_Save_Button_clicked()
{
    if (selectedStudentId.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select a student first.");
        return;
    }
    
    QString firstName = ui->nameLineEdit->text().trimmed();
    QString lastName = ui->LastName->text().trimmed();
    QString email = ui->emailLineEdit->text().trimmed();
    QString password = ui->passwordLineEdit->text();
    
    
    if (firstName.isEmpty() || email.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Error", "All fields must be filled out.");
        return;
    }
    
    
    if (password.length() < 8) {
        QMessageBox::warning(this, "Error", "Password must be at least 8 characters long.");
        return;
    }
    
    bool hasNumber = false;
    for (const QChar &ch : password) {
        if (ch.isDigit()) {
            hasNumber = true;
            break;
        }
    }
    
    if (!hasNumber) {
        QMessageBox::warning(this, "Error", "Password must contain at least one number.");
        return;
    }
    
    
    r.loadstudents();
    bool found = false;
    for (auto &student : r.studentList) {
        if (student.id == selectedStudentId) {
            student.firstName = firstName;
            student.lastName = lastName;
            student.email = email;
            student.password = password;
            found = true;
            break;
        }
    }
    
    if (found) {
        r.savestudents();
        QMessageBox::information(this, "Success", "Student updated successfully.");
        populateStudentsList();
        selectedStudentId = "";
        
        ui->idLineEdit->clear();
        ui->nameLineEdit->clear();
        ui->LastName->clear();
        ui->emailLineEdit->clear();
        ui->passwordLineEdit->clear();
    } else {
        QMessageBox::warning(this, "Error", "Student not found.");
    }
}

void EditStudent::on_Cancel_Button_clicked()
{
    hide();
}


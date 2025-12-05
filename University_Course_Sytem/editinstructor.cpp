#include "editinstructor.h"
#include "ui_editinstructor.h"
#include "registration_system.h"
#include <QMessageBox>
#include <QTableWidgetItem>

EditInstructor::EditInstructor(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditInstructor)
    , selectedInstructorId("")
{
    ui->setupUi(this);
    populateInstructorsList();
}

EditInstructor::~EditInstructor()
{
    delete ui;
}

void EditInstructor::populateInstructorsList()
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
    
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->resizeColumnsToContents();
}

void EditInstructor::on_Select_Button_clicked()
{
    int currentRow = ui->tableWidget->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Error", "Please select an instructor from the table.");
        return;
    }
    
    QTableWidgetItem *idItem = ui->tableWidget->item(currentRow, 0);
    if (!idItem) {
        QMessageBox::warning(this, "Error", "Invalid selection.");
        return;
    }
    
    selectedInstructorId = idItem->text();
    
    
    r.loadinstructors();
    for (const auto &instructor : r.instructorList) {
        if (instructor.InstructorId == selectedInstructorId) {
            ui->idLineEdit->setText(instructor.InstructorId);
            ui->nameLineEdit->setText(instructor.FirstName);
            ui->LastName->setText(instructor.LastName);
            ui->emailLineEdit->setText(instructor.Email);
            ui->passwordLineEdit->setText(instructor.instructorPassword);
            break;
        }
    }
}

void EditInstructor::on_Save_Button_clicked()
{
    if (selectedInstructorId.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select an instructor first.");
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
    
    
    r.loadinstructors();
    bool found = false;
    for (auto &instructor : r.instructorList) {
        if (instructor.InstructorId == selectedInstructorId) {
            instructor.FirstName = firstName;
            instructor.LastName = lastName;
            instructor.Email = email;
            instructor.instructorPassword = password;
            found = true;
            break;
        }
    }
    
    if (found) {
        r.saveinstructors();
        QMessageBox::information(this, "Success", "Instructor updated successfully.");
        populateInstructorsList();
        selectedInstructorId = "";
        
        ui->idLineEdit->clear();
        ui->nameLineEdit->clear();
        ui->LastName->clear();
        ui->emailLineEdit->clear();
        ui->passwordLineEdit->clear();
    } else {
        QMessageBox::warning(this, "Error", "Instructor not found.");
    }
}

void EditInstructor::on_Cancel_Button_clicked()
{
    hide();
}


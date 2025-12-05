#include "editcourse.h"
#include "ui_editcourse.h"
#include "registration_system.h"
#include <QMessageBox>
#include <QTableWidgetItem>

EditCourse::EditCourse(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditCourse)
    , selectedCourseId("")
{
    ui->setupUi(this);
    populateCoursesList();
}

EditCourse::~EditCourse()
{
    delete ui;
}

void EditCourse::populateCoursesList()
{
    r.loadinstructors();
    r.loadcourses();
    
    QTableWidget *table = ui->tableWidget;
    table->setColumnCount(7);
    QStringList headers;
    headers << "Course ID" << "Course Name" << "Instructor" << "Department" 
            << "Credit Hours" << "Time Slot" << "Max Enrollment";
    table->setHorizontalHeaderLabels(headers);
    
    table->setRowCount(r.courseList.size());
    
    for (int i = 0; i < r.courseList.size(); ++i) {
        const Course &course = r.courseList[i];
        table->setItem(i, 0, new QTableWidgetItem(course.id));
        table->setItem(i, 1, new QTableWidgetItem(course.name));
        table->setItem(i, 2, new QTableWidgetItem(r.getInstructorName(course.instructorId)));
        table->setItem(i, 3, new QTableWidgetItem(course.department));
        table->setItem(i, 4, new QTableWidgetItem(QString::number(course.creditHours)));
        table->setItem(i, 5, new QTableWidgetItem(course.timeSlot));
        table->setItem(i, 6, new QTableWidgetItem(QString::number(course.maxEnrollment)));
        
        for (int j = 0; j < 7; j++) {
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

void EditCourse::on_Select_Button_clicked()
{
    int currentRow = ui->tableWidget->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Error", "Please select a course from the table.");
        return;
    }
    
    QTableWidgetItem *idItem = ui->tableWidget->item(currentRow, 0);
    if (!idItem) {
        QMessageBox::warning(this, "Error", "Invalid selection.");
        return;
    }
    
    selectedCourseId = idItem->text();
    
    
    r.loadcourses();
    for (const auto &course : r.courseList) {
        if (course.id == selectedCourseId) {
            ui->idLineEdit->setText(course.id);
            ui->nameLineEdit->setText(course.name);
            ui->instructorLineEdit->setText(course.instructorId);
            ui->departmentLineEdit->setText(course.department);
            ui->creditsLineEdit->setText(QString::number(course.creditHours));
            ui->timeSlotLineEdit->setText(course.timeSlot);
            ui->maxEnrollmentLineEdit->setText(QString::number(course.maxEnrollment));
            break;
        }
    }
}

void EditCourse::on_Save_Button_clicked()
{
    if (selectedCourseId.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select a course first.");
        return;
    }
    
    QString name = ui->nameLineEdit->text();
    QString instructor = ui->instructorLineEdit->text();
    QString department = ui->departmentLineEdit->text();
    QString creditsStr = ui->creditsLineEdit->text();
    QString timeSlot = ui->timeSlotLineEdit->text();
    QString maxEnrollStr = ui->maxEnrollmentLineEdit->text();
    
    
    if (name.isEmpty() || instructor.isEmpty() || department.isEmpty() || 
        creditsStr.isEmpty() || timeSlot.isEmpty() || maxEnrollStr.isEmpty()) {
        QMessageBox::warning(this, "Error", "All fields must be filled out.");
        return;
    }
    
    bool creditOk, enrollmentOk;
    int creditHours = creditsStr.toInt(&creditOk);
    int maxEnrollment = maxEnrollStr.toInt(&enrollmentOk);
    
    if (!creditOk || !enrollmentOk || creditHours <= 0 || maxEnrollment <= 0) {
        QMessageBox::warning(this, "Error", "Credit hours and max enrollment must be positive numbers.");
        return;
    }
    
    
    r.loadcourses();
    bool found = false;
    for (auto &course : r.courseList) {
        if (course.id == selectedCourseId) {
            course.name = name;
            course.instructorId = instructor;
            course.department = department;
            course.creditHours = creditHours;
            course.timeSlot = timeSlot;
            course.maxEnrollment = maxEnrollment;
            found = true;
            break;
        }
    }
    
    if (found) {
        r.savecourses();
        QMessageBox::information(this, "Success", "Course updated successfully.");
        populateCoursesList();
        selectedCourseId = "";
        
        ui->idLineEdit->clear();
        ui->nameLineEdit->clear();
        ui->instructorLineEdit->clear();
        ui->departmentLineEdit->clear();
        ui->creditsLineEdit->clear();
        ui->timeSlotLineEdit->clear();
        ui->maxEnrollmentLineEdit->clear();
    } else {
        QMessageBox::warning(this, "Error", "Course not found.");
    }
}

void EditCourse::on_Cancel_Button_clicked()
{
    hide();
}


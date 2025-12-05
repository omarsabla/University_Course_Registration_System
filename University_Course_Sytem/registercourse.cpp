#include "registercourse.h"
#include "ui_registercourse.h"
#include "registration_system.h"
#include "course.h"
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QHeaderView>
#include <QFont>

registercourse::registercourse(const Student &student, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::registercourse)
    , currentStudent(student)
{
    ui->setupUi(this);
    populateCoursesTable();
    
    
    connect(ui->tableWidget, &QTableWidget::itemSelectionChanged, this, [this]() {
        int currentRow = ui->tableWidget->currentRow();
        if (currentRow >= 0) {
            QTableWidgetItem *idItem = ui->tableWidget->item(currentRow, 0);
            if (idItem) {
                ui->courseID_LineEdit->setText(idItem->text());
            }
        }
    });
    
    
    if (ui->searchLineEdit) {
        connect(ui->searchLineEdit, &QLineEdit::textChanged, this, &registercourse::on_searchLineEdit_textChanged);
    }
}

registercourse::~registercourse()
{
    delete ui;
}

void registercourse::populateCoursesTable()
{
    
    r.loadinstructors();
    r.loadcourses();
    
    
    QTableWidget *table = ui->tableWidget;
    
    
    table->setColumnCount(8);
    QStringList headers;
    headers << "Course ID" << "Course Name" << "Instructor" << "Department"
            << "Credit Hours" << "Time Slot" << "Enrollment" << "Status";
    table->setHorizontalHeaderLabels(headers);
    
    
    int courseCount = r.courseList.size();
    table->setRowCount(courseCount);
    
    if (courseCount == 0) {
        return;
    }
    
    
    for (int i = 0; i < courseCount; ++i) {
        const Course &course = r.courseList[i];
        
        
        table->setItem(i, 0, new QTableWidgetItem(course.id));
        
        
        table->setItem(i, 1, new QTableWidgetItem(course.name));
        
        
        table->setItem(i, 2, new QTableWidgetItem(r.getInstructorName(course.instructorId)));
        
        
        table->setItem(i, 3, new QTableWidgetItem(course.department));
        
        
        table->setItem(i, 4, new QTableWidgetItem(QString::number(course.creditHours)));
        
        
        table->setItem(i, 5, new QTableWidgetItem(course.timeSlot));
        
        
        QString enrollment = QString::number(course.enrolledStudents.size()) + "/" + QString::number(course.maxEnrollment);
        table->setItem(i, 6, new QTableWidgetItem(enrollment));
        
        
        QString status;
        if (course.isFull()) {
            status = "Full";
        } else {
            status = "Available";
        }
        table->setItem(i, 7, new QTableWidgetItem(status));
        
        
        for (int j = 0; j < 8; j++) {
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
    header->setDefaultSectionSize(100);
    header->setStretchLastSection(false);
    header->setSectionResizeMode(QHeaderView::Interactive);
    
    QFont headerFont = header->font();
    headerFont.setBold(true);
    headerFont.setPointSize(10);
    header->setFont(headerFont);
    
    
    table->setColumnWidth(0, 100);  
    table->setColumnWidth(1, 180);  
    table->setColumnWidth(2, 120);  
    table->setColumnWidth(3, 120);  
    table->setColumnWidth(4, 100);  
    table->setColumnWidth(5, 120);  
    table->setColumnWidth(6, 100);  
    table->setColumnWidth(7, 100);  
    
    table->resizeColumnsToContents();
    table->verticalHeader()->setDefaultSectionSize(30);
    table->verticalHeader()->setVisible(true);
}

void registercourse::on_Register_Button_clicked()
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
    
    QString courseId = idItem->text();
    
    
    r.loadcourses();
    r.loadstudents();
    
    
    Course *selectedCourse = nullptr;
    for (auto &course : r.courseList) {
        if (course.id == courseId) {
            selectedCourse = &course;
            break;
        }
    }
    
    if (!selectedCourse) {
        QMessageBox::warning(this, "Error", "Course not found.");
        return;
    }
    
    
    Student *student = nullptr;
    for (auto &s : r.studentList) {
        if (s.id == currentStudent.id) {
            student = &s;
            currentStudent = s; 
            break;
        }
    }
    
    if (!student) {
        QMessageBox::warning(this, "Error", "Student data not found.");
        return;
    }
    
    
    if (student->alreadyRegistered(*selectedCourse)) {
        QMessageBox::warning(this, "Error", "You are already registered for this course.");
        return;
    }
    
    
    if (student->hasTimeConflict(*selectedCourse)) {
        QMessageBox::warning(this, "Error", "This course conflicts with one of your registered courses.");
        return;
    }
    
    
    if (selectedCourse->isFull()) {
        QMessageBox::information(this, "Waitlist", "Course is full. You will be added to the waitlist.");
    }
    
    
    selectedCourse->enrollStudent(*student);
    
    
    student->addCourse(*selectedCourse);
    
    
    r.savestudents();
    r.savecourses();
    
    QMessageBox::information(this, "Success", "Successfully registered for " + selectedCourse->name + "!");
    
    
    populateCoursesTable();
}

void registercourse::on_Done_Button_clicked()
{
    hide();
}

void registercourse::on_searchLineEdit_textChanged(const QString &text)
{
    filterCoursesTable(text);
}

void registercourse::filterCoursesTable(const QString &searchText)
{
    QTableWidget *table = ui->tableWidget;
    
    
    if (searchText.isEmpty()) {
        for (int i = 0; i < table->rowCount(); ++i) {
            table->showRow(i);
        }
        return;
    }
    
    QString searchLower = searchText.toLower();
    
    
    for (int i = 0; i < table->rowCount(); ++i) {
        bool match = false;
        
        
        for (int j = 0; j < table->columnCount(); ++j) {
            QTableWidgetItem *item = table->item(i, j);
            if (item) {
                QString itemText = item->text().toLower();
                if (itemText.contains(searchLower)) {
                    match = true;
                    break;
                }
            }
        }
        
        
        if (match) {
            table->showRow(i);
        } else {
            table->hideRow(i);
        }
    }
}


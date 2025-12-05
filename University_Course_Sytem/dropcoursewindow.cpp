#include "dropcoursewindow.h"
#include "ui_dropcoursewindow.h"
#include "registration_system.h"
#include "course.h"
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QHeaderView>
#include <QFont>

dropcoursewindow::dropcoursewindow(const Student &student, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::dropcoursewindow)
    , currentStudent(student)
{
    ui->setupUi(this);
    populateRegisteredCoursesTable();
    
    
    connect(ui->tableWidget, &QTableWidget::itemSelectionChanged, this, [this]() {
        int currentRow = ui->tableWidget->currentRow();
        if (currentRow >= 0) {
            QTableWidgetItem *idItem = ui->tableWidget->item(currentRow, 0);
            if (idItem) {
                ui->lineEdit->setText(idItem->text());
            }
        }
    });
}

dropcoursewindow::~dropcoursewindow()
{
    delete ui;
}

void dropcoursewindow::populateRegisteredCoursesTable()
{
    
    r.loadstudents();
    r.loadinstructors();
    r.loadcourses();
    
    
    for (const auto &student : r.studentList) {
        if (student.id == currentStudent.id) {
            currentStudent = student;
            break;
        }
    }
    
    
    QTableWidget *table = ui->tableWidget;
    
    
    table->clear();
    table->setRowCount(0);
    
    
    table->setColumnCount(7);
    QStringList headers;
    headers << "Course ID" << "Course Name" << "Instructor" << "Department"
            << "Credit Hours" << "Time Slot" << "Status";
    table->setHorizontalHeaderLabels(headers);
    
    
    int courseCount = currentStudent.registered.size();
    table->setRowCount(courseCount);
    
    if (courseCount == 0) {
        return;
    }
    
    
    for (int i = 0; i < courseCount; ++i) {
        const Course &course = currentStudent.registered[i];
        
        
        table->setItem(i, 0, new QTableWidgetItem(course.id));
        
        
        table->setItem(i, 1, new QTableWidgetItem(course.name));
        
        
        table->setItem(i, 2, new QTableWidgetItem(r.getInstructorName(course.instructorId)));
        
        
        table->setItem(i, 3, new QTableWidgetItem(course.department));
        
        
        table->setItem(i, 4, new QTableWidgetItem(QString::number(course.creditHours)));
        
        
        table->setItem(i, 5, new QTableWidgetItem(course.timeSlot));
        
        
        QString status = "Enrolled";
        
        for (const auto &c : r.courseList) {
            if (c.id == course.id) {
                bool onWaitlist = false;
                for (const auto &waiting : c.waitingList) {
                    if (waiting.id == currentStudent.id) {
                        onWaitlist = true;
                        break;
                    }
                }
                if (onWaitlist) {
                    status = "Waitlisted";
                }
                break;
            }
        }
        table->setItem(i, 6, new QTableWidgetItem(status));
        
        
        for (int j = 0; j < 7; j++) {
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
    
    table->resizeColumnsToContents();
    table->verticalHeader()->setDefaultSectionSize(30);
    table->verticalHeader()->setVisible(true);
    table->setVisible(true);
    table->show();
}

void dropcoursewindow::on_Drop_clicked()
{
    QString courseId = ui->lineEdit->text().trimmed();
    
    if (courseId.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter a course ID or select a course from the table.");
        return;
    }
    
    
    r.loadstudents();
    r.loadcourses();
    
    
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
    
    
    bool isRegistered = false;
    Course *courseToDrop = nullptr;
    
    for (auto &course : r.courseList) {
        if (course.id == courseId) {
            courseToDrop = &course;
            
            for (const auto &enrolled : course.enrolledStudents) {
                if (enrolled.id == student->id) {
                    isRegistered = true;
                    break;
                }
            }
            if (!isRegistered) {
                for (const auto &waiting : course.waitingList) {
                    if (waiting.id == student->id) {
                        isRegistered = true;
                        break;
                    }
                }
            }
            break;
        }
    }
    
    if (!isRegistered) {
        QMessageBox::warning(this, "Error", "You are not registered for this course.");
        return;
    }
    
    if (!courseToDrop) {
        QMessageBox::warning(this, "Error", "Course not found.");
        return;
    }
    
    
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirm Drop", 
        "Are you sure you want to drop " + courseToDrop->name + "?", 
        QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        
        courseToDrop->dropStudent(student->id);
        
        
        for (auto it = student->registered.begin(); it != student->registered.end(); ) {
            if (it->id == courseId) {
                it = student->registered.erase(it);
                break;
            } else {
                ++it;
            }
        }
        
        
        r.savestudents();
        r.savecourses();
        
        QMessageBox::information(this, "Success", "Successfully dropped " + courseToDrop->name + "!");
        
        
        populateRegisteredCoursesTable();
        
        
        ui->lineEdit->clear();
    }
}

void dropcoursewindow::on_cancel_clicked()
{
    hide();
}


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
    
    //connect table selection to update course id line edit
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
    //reload student data
    r.loadstudents();
    r.loadcourses();
    
    //find and update student
    for (const auto &student : r.studentList) {
        if (student.id == currentStudent.id) {
            currentStudent = student;
            break;
        }
    }
    
    //setup table
    QTableWidget *table = ui->tableWidget;
    
    //clear existing items
    table->clear();
    table->setRowCount(0);
    
    //set column count and headers
    table->setColumnCount(7);
    QStringList headers;
    headers << "Course ID" << "Course Name" << "Instructor" << "Department"
            << "Credit Hours" << "Time Slot" << "Status";
    table->setHorizontalHeaderLabels(headers);
    
    //set row count
    int courseCount = currentStudent.registered.size();
    table->setRowCount(courseCount);
    
    if (courseCount == 0) {
        return;
    }
    
    //populate table with registered course data
    for (int i = 0; i < courseCount; ++i) {
        const Course &course = currentStudent.registered[i];
        
        //set course id
        table->setItem(i, 0, new QTableWidgetItem(course.id));
        
        //set course name
        table->setItem(i, 1, new QTableWidgetItem(course.name));
        
        //set instructor
        table->setItem(i, 2, new QTableWidgetItem(course.instructor));
        
        //set department
        table->setItem(i, 3, new QTableWidgetItem(course.department));
        
        //set credit hours
        table->setItem(i, 4, new QTableWidgetItem(QString::number(course.creditHours)));
        
        //set time slot
        table->setItem(i, 5, new QTableWidgetItem(course.timeSlot));
        
        //set status
        QString status = "Enrolled";
        //check in actual course data if student is on waitlist
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
        
        //make all items non-editable
        for (int j = 0; j < 7; j++) {
            QTableWidgetItem *item = table->item(i, j);
            if (item) {
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            }
        }
    }
    
    //formatting options
    table->setAlternatingRowColors(true);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setShowGrid(true);
    table->setSortingEnabled(true);
    
    //style the header
    QHeaderView *header = table->horizontalHeader();
    header->setDefaultSectionSize(100);
    header->setStretchLastSection(false);
    header->setSectionResizeMode(QHeaderView::Interactive);
    
    QFont headerFont = header->font();
    headerFont.setBold(true);
    headerFont.setPointSize(10);
    header->setFont(headerFont);
    
    //set column widths
    table->setColumnWidth(0, 100);  //course id
    table->setColumnWidth(1, 180);  //course name
    table->setColumnWidth(2, 120);  //instructor
    table->setColumnWidth(3, 120);  //department
    table->setColumnWidth(4, 100);  //credit hours
    table->setColumnWidth(5, 120);  //time slot
    table->setColumnWidth(6, 100);  //status
    
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
    
    //reload data
    r.loadstudents();
    r.loadcourses();
    
    //find the current student in the list
    Student *student = nullptr;
    for (auto &s : r.studentList) {
        if (s.id == currentStudent.id) {
            student = &s;
            currentStudent = s; //update current student data
            break;
        }
    }
    
    if (!student) {
        QMessageBox::warning(this, "Error", "Student data not found.");
        return;
    }
    
    //check if student is registered for this course
    bool isRegistered = false;
    Course *courseToDrop = nullptr;
    
    for (auto &course : r.courseList) {
        if (course.id == courseId) {
            courseToDrop = &course;
            //check if student is enrolled or waitlisted
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
    
    //confirm deletion
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirm Drop", 
        "Are you sure you want to drop " + courseToDrop->name + "?", 
        QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        //drop student from course
        courseToDrop->dropStudent(student->id);
        
        //remove course from student's registered list
        for (auto it = student->registered.begin(); it != student->registered.end(); ) {
            if (it->id == courseId) {
                it = student->registered.erase(it);
                break;
            } else {
                ++it;
            }
        }
        
        //save changes
        r.savestudents();
        r.savecourses();
        
        QMessageBox::information(this, "Success", "Successfully dropped " + courseToDrop->name + "!");
        
        //refresh the table
        populateRegisteredCoursesTable();
        
        //clear the line edit
        ui->lineEdit->clear();
    }
}

void dropcoursewindow::on_cancel_clicked()
{
    hide();
}


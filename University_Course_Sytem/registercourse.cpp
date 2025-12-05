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
    
    //connect table selection to update course id line edit
    connect(ui->tableWidget, &QTableWidget::itemSelectionChanged, this, [this]() {
        int currentRow = ui->tableWidget->currentRow();
        if (currentRow >= 0) {
            QTableWidgetItem *idItem = ui->tableWidget->item(currentRow, 0);
            if (idItem) {
                ui->courseID_LineEdit->setText(idItem->text());
            }
        }
    });
    
    //connect search line edit if it exists
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
    //load courses
    r.loadcourses();
    
    //setup table
    QTableWidget *table = ui->tableWidget;
    
    //set column count and headers
    table->setColumnCount(8);
    QStringList headers;
    headers << "Course ID" << "Course Name" << "Instructor" << "Department"
            << "Credit Hours" << "Time Slot" << "Enrollment" << "Status";
    table->setHorizontalHeaderLabels(headers);
    
    //set row count
    int courseCount = r.courseList.size();
    table->setRowCount(courseCount);
    
    if (courseCount == 0) {
        return;
    }
    
    //populate table with course data
    for (int i = 0; i < courseCount; ++i) {
        const Course &course = r.courseList[i];
        
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
        
        //set enrollment
        QString enrollment = QString::number(course.enrolledStudents.size()) + "/" + QString::number(course.maxEnrollment);
        table->setItem(i, 6, new QTableWidgetItem(enrollment));
        
        //set status
        QString status;
        if (course.isFull()) {
            status = "Full";
        } else {
            status = "Available";
        }
        table->setItem(i, 7, new QTableWidgetItem(status));
        
        //make all items non-editable
        for (int j = 0; j < 8; j++) {
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
    table->setColumnWidth(6, 100);  //enrollment
    table->setColumnWidth(7, 100);  //status
    
    table->resizeColumnsToContents();
    table->verticalHeader()->setDefaultSectionSize(30);
    table->verticalHeader()->setVisible(true);
}

void registercourse::on_Register_Button_clicked()
{
    //get selected row
    int currentRow = ui->tableWidget->currentRow();
    
    if (currentRow < 0) {
        QMessageBox::warning(this, "Error", "Please select a course from the table.");
        return;
    }
    
    //get course id from selected row
    QTableWidgetItem *idItem = ui->tableWidget->item(currentRow, 0);
    if (!idItem) {
        QMessageBox::warning(this, "Error", "Invalid selection.");
        return;
    }
    
    QString courseId = idItem->text();
    
    //reload courses and students
    r.loadcourses();
    r.loadstudents();
    
    //find the course
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
    
    //check if already registered
    if (student->alreadyRegistered(*selectedCourse)) {
        QMessageBox::warning(this, "Error", "You are already registered for this course.");
        return;
    }
    
    //check for time conflict
    if (student->hasTimeConflict(*selectedCourse)) {
        QMessageBox::warning(this, "Error", "This course conflicts with one of your registered courses.");
        return;
    }
    
    //check if course is full
    if (selectedCourse->isFull()) {
        QMessageBox::information(this, "Waitlist", "Course is full. You will be added to the waitlist.");
    }
    
    //enroll the student
    selectedCourse->enrollStudent(*student);
    
    //add course to student's registered list
    student->addCourse(*selectedCourse);
    
    //save changes
    r.savestudents();
    r.savecourses();
    
    QMessageBox::information(this, "Success", "Successfully registered for " + selectedCourse->name + "!");
    
    //refresh the table
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
    
    //if search is empty, show all rows
    if (searchText.isEmpty()) {
        for (int i = 0; i < table->rowCount(); ++i) {
            table->showRow(i);
        }
        return;
    }
    
    QString searchLower = searchText.toLower();
    
    //filter rows based on search text
    for (int i = 0; i < table->rowCount(); ++i) {
        bool match = false;
        
        //check all columns for match
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
        
        //show or hide row based on match
        if (match) {
            table->showRow(i);
        } else {
            table->hideRow(i);
        }
    }
}


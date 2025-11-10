#include "CourseManagement.h"
#include "ui_CourseManagement.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QInputDialog>
#include <QFileInfo>

CourseManagement::CourseManagement(QWidget *parent)
    : QWidget(parent), ui(new Ui::CourseManagement)
{
    ui->setupUi(this);
    connect(ui->searchButton, &QPushButton::clicked, this, &CourseManagement::searchCourses);
    connect(ui->addButton, &QPushButton::clicked, this, &CourseManagement::addCourse);
    connect(ui->editButton, &QPushButton::clicked, this, &CourseManagement::editCourse);
    connect(ui->deleteButton, &QPushButton::clicked, this, &CourseManagement::deleteCourse);
    createDefaultCoursesIfMissing();
    loadCoursesFromFile();
    refreshTable();
}

CourseManagement::~CourseManagement() {
    saveCoursesToFile();
    delete ui;
}

void CourseManagement::createDefaultCoursesIfMissing() {
    QFileInfo check(filePath);
    if (check.exists() && check.isFile()) return;
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;
    QTextStream out(&file);
    out << "CSCE1102|Programming2|Dr. Omar|Computer Science|3|Mon 10-12|30\n";
    out << "MATH101|Calculus1|Dr. Eman|Mathematics|3|Sun 8-10|30\n";
    out << "PHYS101|Physics1|Dr. Hana|Physics|3|Tue 10-12|30\n";
    out << "CORE101|Humanities|Dr. Sara|Humanities|3|Wed 12-2|30\n";
    file.close();
}

void CourseManagement::loadCoursesFromFile() {
    courses.clear();
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (!line.isEmpty())
            courses.append(Course::fromString(line));
    }
    file.close();
}

void CourseManagement::saveCoursesToFile() {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;
    QTextStream out(&file);
    for (const Course &c : courses)
        out << c.toString() << "\n";
    file.close();
}

void CourseManagement::refreshTable() {
    ui->courseTable->clearContents();
    ui->courseTable->setRowCount(courses.size());
    ui->courseTable->setColumnCount(6);
    QStringList headers = {"ID", "Name", "Instructor", "Department", "Credits", "Schedule"};
    ui->courseTable->setHorizontalHeaderLabels(headers);
    for (int r = 0; r < courses.size(); ++r) {
        const Course &c = courses[r];
        ui->courseTable->setItem(r, 0, new QTableWidgetItem(c.courseID));
        ui->courseTable->setItem(r, 1, new QTableWidgetItem(c.courseName));
        ui->courseTable->setItem(r, 2, new QTableWidgetItem(c.instructor));
        ui->courseTable->setItem(r, 3, new QTableWidgetItem(c.department));
        ui->courseTable->setItem(r, 4, new QTableWidgetItem(QString::number(c.creditHours)));
        ui->courseTable->setItem(r, 5, new QTableWidgetItem(c.scheduleTime));
    }
    ui->courseTable->resizeColumnsToContents();
}

void CourseManagement::searchCourses() {
    QString q = ui->searchInput->text().trimmed();
    if (q.isEmpty()) {
        refreshTable();
        return;
    }
    ui->courseTable->setRowCount(0);
    for (const Course &c : courses) {
        if (c.instructor.contains(q, Qt::CaseInsensitive) ||
            c.department.contains(q, Qt::CaseInsensitive) ||
            c.scheduleTime.contains(q, Qt::CaseInsensitive)) {
            int newRow = ui->courseTable->rowCount();
            ui->courseTable->insertRow(newRow);
            ui->courseTable->setItem(newRow, 0, new QTableWidgetItem(c.courseID));
            ui->courseTable->setItem(newRow, 1, new QTableWidgetItem(c.courseName));
            ui->courseTable->setItem(newRow, 2, new QTableWidgetItem(c.instructor));
            ui->courseTable->setItem(newRow, 3, new QTableWidgetItem(c.department));
            ui->courseTable->setItem(newRow, 4, new QTableWidgetItem(QString::number(c.creditHours)));
            ui->courseTable->setItem(newRow, 5, new QTableWidgetItem(c.scheduleTime));
        }
    }
}

void CourseManagement::addCourse() {
    QString id = QInputDialog::getText(this, "Add Course", "Course ID:");
    if (id.isEmpty()) return;
    for (const Course &c : courses)
        if (c.courseID == id) {
            QMessageBox::warning(this, "Error", "Duplicate Course ID!");
            return;
        }
    QString name = QInputDialog::getText(this, "Add Course", "Course Name:");
    QString instr = QInputDialog::getText(this, "Add Course", "Instructor:");
    QString dept = QInputDialog::getText(this, "Add Course", "Department:");
    int credits = 3;
    QString sched = QInputDialog::getText(this, "Add Course", "Schedule:");
    int max = 30;
    courses.append(Course(id, name, instr, dept, credits, sched, max));
    saveCoursesToFile();
    refreshTable();
}

void CourseManagement::editCourse() {
    int row = ui->courseTable->currentRow();
    if (row < 0 || row >= courses.size()) return;
    Course &c = courses[row];
    c.courseName = QInputDialog::getText(this, "Edit Course", "Course Name:", QLineEdit::Normal, c.courseName);
    c.instructor = QInputDialog::getText(this, "Edit Course", "Instructor:", QLineEdit::Normal, c.instructor);
    c.department = QInputDialog::getText(this, "Edit Course", "Department:", QLineEdit::Normal, c.department);
    c.scheduleTime = QInputDialog::getText(this, "Edit Course", "Schedule:", QLineEdit::Normal, c.scheduleTime);
    saveCoursesToFile();
    refreshTable();
}

void CourseManagement::deleteCourse() {
    int row = ui->courseTable->currentRow();
    if (row < 0 || row >= courses.size()) return;
    if (QMessageBox::question(this, "Delete", "Delete selected course?") != QMessageBox::Yes) return;
    courses.removeAt(row);
    saveCoursesToFile();
    refreshTable();
}

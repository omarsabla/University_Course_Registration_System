#ifndef VIEWDELETECOURSE_H
#define VIEWDELETECOURSE_H

#include <QDialog>

namespace Ui {
class viewdeletecourse;
}

class viewdeletecourse : public QDialog
{
    Q_OBJECT

public:
    explicit viewdeletecourse(QWidget *parent = nullptr);
    ~viewdeletecourse();

private slots:
    void on_searchLineEdit_textChanged(const QString &arg1);
    void on_Delete_Button_clicked();
    void on_Done_Button_clicked();
    void filterTable(const QString &searchText);

private:
    Ui::viewdeletecourse *ui;
    void populateTable();
};

#endif 


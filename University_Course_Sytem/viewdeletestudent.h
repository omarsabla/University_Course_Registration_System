#ifndef VIEWDELETESTUDENT_H
#define VIEWDELETESTUDENT_H

#include <QDialog>

namespace Ui {
class viewdeletestudent;
}

class viewdeletestudent : public QDialog
{
    Q_OBJECT

public:
    explicit viewdeletestudent(QWidget *parent = nullptr);
    ~viewdeletestudent();

private slots:
    void on_searchLineEdit_textChanged(const QString &arg1);
    void on_Delete_Button_clicked();
    void on_Done_Button_clicked();
    void filterTable(const QString &searchText);

private:
    Ui::viewdeletestudent *ui;
    void populateTable();
};

#endif // VIEWDELETESTUDENT_H


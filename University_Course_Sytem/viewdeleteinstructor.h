#ifndef VIEWDELETEINSTRUCTOR_H
#define VIEWDELETEINSTRUCTOR_H

#include <QDialog>

namespace Ui {
class viewdeleteinstructor;
}

class viewdeleteinstructor : public QDialog
{
    Q_OBJECT

public:
    explicit viewdeleteinstructor(QWidget *parent = nullptr);
    ~viewdeleteinstructor();

private slots:
    void on_searchLineEdit_textChanged(const QString &arg1);
    void on_Delete_Button_clicked();
    void on_Done_Button_clicked();
    void filterTable(const QString &searchText);

private:
    Ui::viewdeleteinstructor *ui;
    void populateTable();
};

#endif 


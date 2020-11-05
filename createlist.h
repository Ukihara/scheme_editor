#ifndef CREATELIST_H
#define CREATELIST_H

#include <QMainWindow>

namespace Ui {
class CreateList;
}

class CreateList : public QMainWindow
{
    Q_OBJECT

public:
    explicit CreateList(QWidget *parent = nullptr);
    ~CreateList();

signals:
    void firstWindow();

private slots:
    void on_closeBut_clicked();
    void on_saveBut_clicked();

private:
    Ui::CreateList *ui;
    CreateList *createlist;
};

#endif // CREATELIST_H

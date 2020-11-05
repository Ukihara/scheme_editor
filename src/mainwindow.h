#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>

//подключаем окно "выбор объекта"
#include "choseobj.h"
#include "createlist.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_choseobjBut_clicked();
    void on_createlistBut_clicked();
    void on_countBut_clicked();
    void on_areaBut_clicked();

private:
    Ui::MainWindow *ui;
    //создаём объект окна "выбор"
    ChoseObj *choseobj;
    CreateList *createlist;
    QLineEdit *countLine;
    QLineEdit *areaLine;
};
#endif // MAINWINDOW_H

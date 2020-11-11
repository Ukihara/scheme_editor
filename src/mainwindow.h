#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>

#include <QLabel>
#include <QLineEdit>
#include <QWidget>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QWidget>
#include <QVector>
#include <QPointF>
#include <QGraphicsScene>


#include "tinyxml2.h"
#include <cstring>
using namespace tinyxml2;

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
    void paint();

private slots:
    void on_choseobjBut_clicked();
    void on_createlistBut_clicked();
    void on_countBut_clicked();
    void on_areaBut_clicked();
    void on_tempBut_clicked();

private:
    Ui::MainWindow *ui;
    //создаём сцену, на которой будет происходить отрисовка объектов
    QGraphicsScene *scene;

    //создаём объекты окон
    ChoseObj *choseobj;
    CreateList *createlist;
    QLineEdit *countLine;
    QLineEdit *areaLine;
};
#endif // MAINWINDOW_H

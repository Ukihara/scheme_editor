#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //инициализируем окно выбора и подключаем к слоту
    //возврата на главное окно кнопку "Готово" на втором окне
    choseobj = new ChoseObj();
    connect(choseobj, &ChoseObj::firstWindow, this, &MainWindow::show);

    createlist = new CreateList();
    connect(createlist, &CreateList::firstWindow, this, &MainWindow::show);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_choseobjBut_clicked()
{
    choseobj->show();
    this->close();
}

void MainWindow::on_createlistBut_clicked()
{
    createlist->show();
    this->close();
}

void MainWindow::on_countBut_clicked()
{
    //здесь считаем количество оборудования и выводим на countLine
    ui->countLine->setText("Вы нажали кнопку");
}

void MainWindow::on_areaBut_clicked()
{
    //здесь считаем площадь и выводим на areaLine
    ui->areaLine->setText("Вы нажали кнопку");
}



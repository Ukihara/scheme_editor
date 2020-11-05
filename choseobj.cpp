#include "choseobj.h"
#include "ui_choseobj.h"

ChoseObj::ChoseObj(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChoseObj)
{
    ui->setupUi(this);

    createobj = new CreateObj();
    connect(createobj, &CreateObj::choseWindow, this, &ChoseObj::show);

}

ChoseObj::~ChoseObj()
{
    delete ui;
}

void ChoseObj::on_readyBut_clicked()
{
    this->close();
    emit firstWindow(); //вызываем сигнал на открытие главного окна
}

void ChoseObj::on_createBut_clicked()
{
    createobj->show();
    this->close();
}

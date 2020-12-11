#include "choseobj.h"
#include "ui_choseobj.h"

ChoseObj::ChoseObj(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChoseObj)
{
    ui->setupUi(this);

//    createobj = new CreateObj();
//    connect(createobj, &CreateObj::choseWindow, this, &ChoseObj::show);
}

ChoseObj::~ChoseObj()
{
    delete ui;
}

void ChoseObj::on_tcompBut_clicked()
{
    this->close();
    emit firstWindow_comp();
}

void ChoseObj::on_tprinterBut_clicked()
{
    this->close();
    emit firstWindow_prin();
}

void ChoseObj::on_trouterBut_clicked()
{
    this->close();
    emit firstWindow_rout();
}

void ChoseObj::createObject_done(QPolygon *p)
{
    this->close();
    emit firstWindow_custom_obj(p);
}

void ChoseObj::on_createBut_clicked()
{
    createobj = new CreateObj();
    connect(createobj, &CreateObj::choseWindow, this, &ChoseObj::show);
    connect(createobj, &CreateObj::createObj, this, &ChoseObj::createObject_done);
    createobj->show();
    this->close();
}

void ChoseObj::on_cancelBut_clicked()
{
    this->close();
    emit firstWindow(); //вызываем сигнал на открытие главного окна
    //здесь больше ничего не будет
}

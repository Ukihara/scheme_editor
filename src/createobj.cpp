#include "createobj.h"
#include "ui_createobj.h"

CreateObj::CreateObj(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CreateObj)
{
    ui->setupUi(this);
}

CreateObj::~CreateObj()
{
    delete ui;
}

void CreateObj::on_readyBut_clicked()
{
    this->close();
    emit choseWindow();
    //здесь будет код, описывающий добавление нарисованной фигуры в список оборудования и отображение на экране выбора
}

void CreateObj::on_cancelBut_clicked()
{
    this->close();
    emit choseWindow();
    //здесь больше ничего не будет
}

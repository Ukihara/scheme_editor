#include "createlist.h"
#include "ui_createlist.h"

CreateList::CreateList(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CreateList)
{
    ui->setupUi(this);
}

CreateList::~CreateList()
{
    delete ui;
}

void CreateList::on_saveBut_clicked()
{

}

void CreateList::on_closeBut_clicked()
{
    this->close();
    emit firstWindow();
}

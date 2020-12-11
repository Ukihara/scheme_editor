#ifndef CHOSEOBJ_H
#define CHOSEOBJ_H

#include <QMainWindow>
#include "createobj.h"

namespace Ui {
class ChoseObj;
}

class ChoseObj : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChoseObj(QWidget *parent = nullptr);
    ~ChoseObj();

signals:
    void firstWindow(); //сигнал для главного окна
    void firstWindow_comp(); //сигнал для отрисовки компьютера
    void firstWindow_prin(); //сигнал для отрисовки принтера
    void firstWindow_rout(); //сигнал для отрисовки роутера
    void firstWindow_custom_obj(QPolygon *p); //сигнал для отрисовки кастомного объекта

private slots:
    //обработка нажатия кнопки "готово"
    void on_createBut_clicked();
    void on_cancelBut_clicked();

    void on_tcompBut_clicked();
    void on_tprinterBut_clicked();
    void on_trouterBut_clicked();

    void createObject_done(QPolygon *p);

private:
    Ui::ChoseObj *ui;
    CreateObj *createobj;
};

#endif //CHOSEOBJ_H


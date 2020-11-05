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

private slots:
    //обработка нажатия кнопки "готово"
    void on_readyBut_clicked();
    void on_createBut_clicked();

private:
    Ui::ChoseObj *ui;
    CreateObj *createobj;
};

#endif //CHOSEOBJ_H


#ifndef CREATEOBJ_H
#define CREATEOBJ_H

#include <QMainWindow>
#include "drawarea.h"

namespace Ui {
class CreateObj;
}

class CreateObj : public QMainWindow
{
    Q_OBJECT

public:
    explicit CreateObj(QWidget *parent = nullptr);
    ~CreateObj();

signals:
    void choseWindow();
    void createObj(QPolygon *p);

private slots:
    void on_readyBut_clicked();
    void on_cancelBut_clicked();

    void on_cancelLastPoint_clicked();

private:
    Ui::CreateObj *ui;
    DrawArea *draw_area;
};

#endif // CREATEOBJ_H

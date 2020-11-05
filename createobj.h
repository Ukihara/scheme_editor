#ifndef CREATEOBJ_H
#define CREATEOBJ_H

#include <QMainWindow>

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

private slots:
    void on_readyBut_clicked();

private:
    Ui::CreateObj *ui;
};

#endif // CREATEOBJ_H

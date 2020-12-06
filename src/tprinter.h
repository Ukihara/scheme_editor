#ifndef TPRINTER_H
#define TPRINTER_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>
#include <QMessageBox>

namespace Ui {
class TPrinter;
}

class TPrinter : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    explicit TPrinter(QObject *parent = nullptr);
    ~TPrinter();

private:
    Ui::TPrinter *ui;

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    qreal pos_x;
    qreal pos_y;

    qreal dx;
    qreal dy;
};

#endif // TPRINTER_H

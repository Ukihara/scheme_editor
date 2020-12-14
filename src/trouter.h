#ifndef TROUTER_H
#define TROUTER_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>
#include <QMessageBox>

namespace Ui {
class TRouter;
}

class TRouter : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    explicit TRouter(QObject *parent = nullptr);
    ~TRouter();

private:
    Ui::TRouter *ui;

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

#endif // TROUTER_H

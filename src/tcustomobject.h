#ifndef TCUSTOMOBJECT_H
#define TCUSTOMOBJECT_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>
#include <QMessageBox>
#include <QTransform>

namespace Ui{
    class TCustomObject;
};

class TCustomObject : public QObject, public QGraphicsPolygonItem
{
    Q_OBJECT
public:
    explicit TCustomObject(QPolygon *poly, QObject *parent = nullptr);
    ~TCustomObject();
    qreal pos_x = 0;
    qreal pos_y = 0;

private:
    Ui::TCustomObject *ui;

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    QPolygon *polygon;

    qreal dx = 0;
    qreal dy = 0;

signals:

};

#endif // TCUSTOMOBJECT_H

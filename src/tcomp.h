#ifndef TCOMP_H
#define TCOMP_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>
#include <QMessageBox>

namespace Ui {
class TComp;
}

class TComp : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    explicit TComp(QObject *parent = nullptr);
    ~TComp();

private:
    Ui::TComp *ui;

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // TCOMP_H

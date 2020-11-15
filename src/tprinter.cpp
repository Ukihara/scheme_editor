#include "tprinter.h"
#include "ui_tprinter.h"

/*Весь класс - копия TComp, искючая название
 * */
TPrinter::TPrinter(QObject *parent) :
    QObject(parent), QGraphicsItem(),
    ui(new Ui::TPrinter)
{

}

TPrinter::~TPrinter()
{

}

QRectF TPrinter::boundingRect() const
{
    return QRectF (0, 0, 60, 30);
}

void TPrinter::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QVector <QPoint> dots;

    dots << QPoint(0, 0) << QPoint(60, 0) << QPoint(60, 20) << QPoint(50, 20)
                << QPoint(50, 20) << QPoint(40, 30) << QPoint(20, 30) << QPoint(10, 20)
                << QPoint(0, 20) << QPoint(0, 0);

    QPolygonF pol(dots);

    painter->setPen(Qt::black);
    painter->setBrush(Qt::green);
    painter->drawPolygon(pol);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void TPrinter::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    this->setPos(mapToScene(event->pos()));
}

void TPrinter::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        this->setCursor(QCursor(Qt::ClosedHandCursor));
    }
    else if (event->button() == Qt::RightButton)
    {
        QMessageBox::StandardButton reply = QMessageBox::question(nullptr, "Удаление", "Вы хотите удалить элемент?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
             scene()->removeItem(this);
        }
    }
    Q_UNUSED(event);
}

void TPrinter::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qreal pos_x = 10;
    qreal pos_y = 10;

    if (!scene()->collidingItems(this).isEmpty()){
        this->setX(pos_x);
        this->setY(pos_y);
    }
    else
        this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}

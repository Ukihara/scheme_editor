#include "trouter.h"
#include "ui_trouter.h"

/*Весь класс - копия TComp, искючая название
 * */
TRouter::TRouter(QObject *parent) :
    QObject(parent), QGraphicsItem(),
    ui(new Ui::TRouter)
{

}

TRouter::~TRouter()
{
    delete ui;
}

static int randomBetween(int low, int high)
{
    return (qrand() % ((high + 1) - low) + low);
}

QRectF TRouter::boundingRect() const
{
    return QRectF (0, 0, 20, 25);
}

void TRouter::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QVector <QPoint> dots;

    dots << QPoint(0, 0) << QPoint(5, 10) << QPoint(0, 10) << QPoint(0, 25)
                << QPoint(20, 25) << QPoint(20, 10) << QPoint(15, 10) << QPoint(20, 0)
                << QPoint(15, 10) << QPoint(5, 10) << QPoint(0, 0);

    QPolygonF pol(dots);

    painter->setPen(Qt::black);
    painter->setBrush(Qt::green);
    painter->drawPolygon(pol);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void TRouter::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    this->setPos(mapToScene(event->pos()));
}

void TRouter::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        this->setCursor(QCursor(Qt::ClosedHandCursor));

        pos_x = this->x();
        pos_y = this->y();
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

void TRouter::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(!scene()->collidingItems(this).isEmpty())
    {
        this->setX(pos_x);
        this->setY(pos_y);
    }
    else
    {
        this->setCursor(QCursor(Qt::ArrowCursor));
    }

    Q_UNUSED(event);
}

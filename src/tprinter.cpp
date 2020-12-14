#include "tprinter.h"
#include "ui_tprinter.h"

/*Весь класс - копия TComp, искючая название
 * */
TPrinter::TPrinter(QObject *parent) :
    QObject(parent), QGraphicsItem(),
    ui(new Ui::TPrinter)
{
    this->dx = 0;
    this->dy = 0;
}

TPrinter::~TPrinter()
{

}

static int randomBetween(int low, int high)
{
    return (qrand() % ((high + 1) - low) + low);
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
    auto pos = event->pos();

    pos.setX(event->pos().rx() - this->dx);
    pos.setY(event->pos().ry() - this->dy);

    if (this->x() > scene()->width() | this->x() < 0 ){
        return;
    }
    if (this->y() > scene()->height() | this->y() < 0 ){
        return;
    }
    this->setPos(mapToScene(pos));
}

void TPrinter::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        this->setCursor(QCursor(Qt::ClosedHandCursor));
        this->dx = event->pos().rx();
        this->dy = event->pos().ry();
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

void TPrinter::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(!scene()->collidingItems(this).isEmpty())
    {
        this->setX(pos_x + dx);
        this->setY(pos_y + dy);
    }
    else
    {
        if (this->x() > scene()->width() ){
            this->setX(this->x() - 10);
            this->mouseReleaseEvent(event);
        }
        else{
            if (this->x() < 0){
                this->setX(this->x() + 10);
                this->mouseReleaseEvent(event);
            }
        }
        if (this->y() > scene()->height() ){
            this->setY(this->y() - 10);
            this->mouseReleaseEvent(event);
        }
        else{
            if (this->y() < 0){
                this->setY(this->y() + 10);
                this->mouseReleaseEvent(event);
            }
        }
        this->setCursor(QCursor(Qt::ArrowCursor));
    }

    Q_UNUSED(event);
}

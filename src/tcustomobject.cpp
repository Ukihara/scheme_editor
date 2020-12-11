#include "tcustomobject.h"
#include "ui_custom_obj.h"

TCustomObject::TCustomObject(QPolygon *poly, QObject *parent) :
    QObject(parent), QGraphicsPolygonItem(),
    ui(new Ui::TCustomObject)
{

    this->polygon = poly;
    this->dx = 0;
    this->dy = 0;
    this->setPolygon(*poly);
}

TCustomObject::~TCustomObject()
{
    delete this->polygon;
}

QRectF TCustomObject::boundingRect() const
{
    return this->polygon->boundingRect();
}

void TCustomObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    QTransform transformer;
//    transformer.scale(0.5, 0.5);
//    painter->setTransform(transformer);

    painter->setPen(Qt::black);
    painter->setBrush(Qt::green);
//    painter->resetTransform();
    painter->drawPolygon(*this->polygon);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void TCustomObject::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    auto pos = event->pos();

    pos.setX(event->pos().rx() - this->dx);
    pos.setY(event->pos().ry() - this->dy);

    this->setPos(mapToScene(pos));
}

void TCustomObject::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "pressed";
    if (event->button() == Qt::LeftButton)
    {
        this->setCursor(QCursor(Qt::ClosedHandCursor));
        this->dx = event->pos().rx();
        this->dy = event->pos().ry();
        pos_x = this->scenePos().rx();
        pos_y = this->scenePos().ry();
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

void TCustomObject::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
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

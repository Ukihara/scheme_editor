#include "tcustomobject.h"
#include "ui_custom_obj.h"

TCustomObject::TCustomObject(QPolygon *poly, QObject *parent) :
    QObject(parent), QGraphicsPolygonItem(poly->translated(-poly->boundingRect().x(), -poly->boundingRect().y())),
    ui(new Ui::TCustomObject)
{
    QRect r = poly->boundingRect();
    poly->translate(-r.x(), -r.y());
    this->polygon = poly;
    this->dx = 0;
    this->dy = 0;
}

TCustomObject::~TCustomObject()
{
//    delete this->polygon;
}

QRectF TCustomObject::boundingRect() const
{
    auto tr = this->polygon->translated(pos_x, pos_y).boundingRect();
//    auto r = this->polygon->boundingRect();
    tr.setCoords(0, 0, tr.width(), tr.height());
//    tr.setHeight(r.height());
//    return this->polygon->translated(pos_x, pos_y).boundingRect();
    return tr;
}

void TCustomObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QTransform transformer;

//    transformer.scale(0.5, 0.5);
//    painter->setTransform(transformer);
    painter->setPen(Qt::black);
    painter->setBrush(Qt::green);
    painter->drawPolygon(this->polygon->translated(pos_x, pos_y));
//    painter->resetTransform();

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void TCustomObject::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
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

void TCustomObject::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "pressed";
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

void TCustomObject::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
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

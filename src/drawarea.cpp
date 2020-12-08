#include "drawarea.h"

DrawArea::DrawArea(QWidget *parent) : QWidget(parent)
{

    this->polygon = new QPolygon;
}

void DrawArea::fillBackground(){
    QPainter painter(this);

    QRect r(0, 0, this->width(), this->height());
    QPainterPath path;
    path.addRect(r);

    painter.fillPath(path, Qt::white);
    painter.drawPath(path);
}

void DrawArea::drawPoly(){
    QPainter painter(this);
    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::black);
    painter.setPen(pen);
    painter.drawPolygon(*this->polygon);
}

void DrawArea::paintEvent(QPaintEvent *event)
{
    this->fillBackground();
    this->drawPoly();
}

void DrawArea::removeLastPoint()
{
    if (this->polygon->length() > 0){
        this->polygon->pop_back();
        this->update();
    }
}


void DrawArea::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        this->polygon->append(event->pos());
        this->update();
    }
}


void DrawArea::mouseMoveEvent(QMouseEvent *event)
{

}

void DrawArea::mouseReleaseEvent(QMouseEvent *event)
{

}

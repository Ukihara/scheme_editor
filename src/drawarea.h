#ifndef DRAWAREA_H
#define DRAWAREA_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QPainterPath>
#include <QPolygon>

class DrawArea : public QWidget
{
    Q_OBJECT
public:
    explicit DrawArea(QWidget *parent = nullptr);
    void removeLastPoint();

    QPolygon *polygon;
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    void fillBackground();
    void drawPoly();

signals:

};

#endif // DRAWAREA_H

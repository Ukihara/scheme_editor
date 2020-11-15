#include "tcomp.h"
#include "ui_tcomp.h"

TComp::TComp(QObject *parent) :
    QObject(parent), QGraphicsItem(),
    ui(new Ui::TComp)
{

}

TComp::~TComp()
{
    delete ui;
}

/* Создаем прямоугольную область, ограничивающую наш объект
 * */
QRectF TComp::boundingRect() const
{
    return QRectF (0, 0, 60, 40);
}

/*Рисуем полигон по точкам
 * */
void TComp::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QVector <QPoint> dots;

    dots << QPoint(40, 20) << QPoint(40, 30) << QPoint(0, 30) <<
            QPoint(0, 20) << QPoint(10, 10) << QPoint(30, 10) << QPoint(40, 20); //monitor

    dots << QPoint(40, 0) << QPoint(60, 0) << QPoint(60, 40) << QPoint(40, 40) <<
            QPoint(40, 30); //block

    QPolygonF pol(dots);

    painter->setPen(Qt::black);
    painter->setBrush(Qt::green);
    painter->drawPolygon(pol);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void TComp::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    /* Устанавливаем позицию графического элемента
     * в графической сцене, транслируя координаты
     * курсора внутри графического элемента
     * в координатную систему графической сцены
     * */
    this->setPos(mapToScene(event->pos()));
}

void TComp::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        /* При нажатии левой мышью на графический элемент
         * заменяем курсор на руку, которая держит этот элемент
         * */
        this->setCursor(QCursor(Qt::ClosedHandCursor));
    }
    else if (event->button() == Qt::RightButton)
    {
        /* Если нажата правая кнопка мыши
         * уточняем, хочет ли пользователь удалить объект со сцены
         * Если да - удаляем
         * */
        QMessageBox::StandardButton reply =
                        QMessageBox::question(nullptr, "Удаление", "Вы хотите удалить элемент?",
                        QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
             scene()->removeItem(this);
        }
    }
    Q_UNUSED(event);
}

void TComp::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    /* При отпускании мышью элемента
     * заменяем на обычный курсор стрелку
     * Прежде всего выполняется проверка - можно ли поставить объект на выбранное место
     * collidingItems возвращает список элементов на основной сцене, с которыми произошла
     * коллизия здешнего элемента
     * */
    qreal pos_x = 10;
    qreal pos_y = 10;

    if (!scene()->collidingItems(this).isEmpty())
    {
        this->setX(pos_x);
        this->setY(pos_y);
    }
    else
        this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}

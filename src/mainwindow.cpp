#include "mainwindow.h"
#include "ui_mainwindow.h"

QString fileName;
const char *fileNameChar = "";
QByteArray tmp;

static int randomBetween(int low, int high)
{
    return (qrand() % ((high + 1) - low) + low);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(1250, 700);
    this->setFixedSize(1300, 700);
    scene = new QGraphicsScene(this);

    //инициализируем окно выбора и подключаем к слоту
    //возврата на главное окно кнопку "Готово" на втором окне
    choseobj = new ChoseObj();
    connect(choseobj, &ChoseObj::firstWindow, this, &MainWindow::show);
    connect(choseobj, &ChoseObj::firstWindow_comp, this, &MainWindow::paint_comp);
    connect(choseobj, &ChoseObj::firstWindow_prin, this, &MainWindow::paint_prin);
    connect(choseobj, &ChoseObj::firstWindow_rout, this, &MainWindow::paint_rout);
    connect(choseobj, &ChoseObj::firstWindow_custom_obj, this, &MainWindow::paint_custom_obj);

    createlist = new CreateList();
    connect(createlist, &CreateList::firstWindow, this, &MainWindow::show);

    ui->choseobjBut->setEnabled(false);
    ui->countBut->setEnabled(false);
    ui->createlistBut->setEnabled(false);
    ui->areaBut->setEnabled(false);
    ui->scaleEdit->setEnabled(false);
    ui->scaleLabel->setEnabled(false);
    ui->scaleLabel_2->setEnabled(false);
    ui->scaleLabel_3->setEnabled(false);
    ui->autoplacement->setEnabled(false);
    ui->areaLine->setEnabled(false);
    ui->countLine->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_choseobjBut_clicked()
{
    choseobj->show();
}

void MainWindow::on_createlistBut_clicked()
{
    createlist->show();
    this->close();
}

void MainWindow::on_countBut_clicked()
{
    //здесь считаем количество оборудования и выводим на countLine
    int num_of_items = 0;
    num_of_items += comps.size();
    num_of_items += printers.size();
    num_of_items += routers.size();
    num_of_items += custom_objects.size();
    QString num;
    num.setNum(num_of_items);
    ui->countLine->setText(num);
}

void MainWindow::on_areaBut_clicked()
{
    //здесь считаем площадь и выводим на areaLine
    QList<QGraphicsItem *> items =  scene->items();
    bool frst = true;
    double square = 0;
    int frst_wall = 1;
    int scnd_wall = 1;
    double meter_scale = ui->scaleEdit->text().toDouble();

    for (auto x : items){
        if (x->boundingRect().height() == 8 || x->boundingRect().width() == 8){ // that means that this wall is main
            if (frst){ // walls should be grouped by room (room1_wall, room1_wall, room2_wall, room2_wall, ... etc)
                frst_wall = x->boundingRect().height() == 8 ? x->boundingRect().width() - 1 : x->boundingRect().height() - 1;
                frst = false;
            }
            else{
                scnd_wall = x->boundingRect().height() == 8 ? x->boundingRect().width() - 1 : x->boundingRect().height() - 1;
                square += frst_wall * scnd_wall;
                frst = true;
                qDebug() << "nth room square : " << frst_wall * scnd_wall;
            }
        }
    }
    ui->areaLine->setText(QString::number(square * meter_scale * meter_scale) + " m^2");
}

void MainWindow::paint_comp()
{
    TComp *item = new TComp();
    item->setPos(randomBetween(30, 900), randomBetween(30, 400));
    comps.push_back(item);
    scene->addItem(item);
    qreal pos_x = randomBetween(30, 900);
    qreal pos_y = randomBetween(30, 400);

    while(!scene->collidingItems(item).isEmpty())
    {
        item->setX(pos_x);
        item->setY(pos_y);
        pos_x = randomBetween(30, 900);
        pos_y = randomBetween(30, 400);
    }
}

void MainWindow::paint_custom_obj(QPolygon *poly)
{
    TCustomObject *item = new TCustomObject(poly);
    custom_objects.push_back(item);
    scene->addItem(item);
    auto max_w =  scene->width() - poly->boundingRect().width() - 300;
    auto max_h = scene->height() - poly->boundingRect().height() - 300;
    qreal pos_x = randomBetween(30, max_w);
    qreal pos_y = randomBetween(30, max_h);
    item->setPos(pos_x, pos_y);
    int max_try_amount = 100000;

    while(!scene->collidingItems(item).isEmpty() && --max_try_amount >= 0)
    {
        pos_x = randomBetween(30, max_w);
        pos_y = randomBetween(30, max_h);
        item->setPos(pos_x, pos_y);
    }
    item->update();
    if (max_try_amount < 0){
        QMessageBox::warning(nullptr, "Ошибка", "Не удалось поместить объект на сцену", QMessageBox::Ok);
        scene->removeItem(item);
        delete item;
    }
}

void MainWindow::paint_prin()
{
    TPrinter *item = new TPrinter();
    item->setPos(randomBetween(30, 900), randomBetween(30, 400));
    printers.push_back(item);
    scene->addItem(item);
    qreal pos_x = randomBetween(30, 900);
    qreal pos_y = randomBetween(30, 400);

    while(!scene->collidingItems(item).isEmpty())
    {
        item->setX(pos_x);
        item->setY(pos_y);
        pos_x = randomBetween(30, 900);
        pos_y = randomBetween(30, 400);
    }
}

void MainWindow::paint_rout()
{
    TRouter *item = new TRouter();
    item->setPos(randomBetween(30, 900), randomBetween(30, 400));
    routers.push_back(item);
    scene->addItem(item);
    qreal pos_x = randomBetween(30, 900);
    qreal pos_y = randomBetween(30, 400);

    while(!scene->collidingItems(item).isEmpty())
    {
        item->setX(pos_x);
        item->setY(pos_y);
        pos_x = randomBetween(30, 900);
        pos_y = randomBetween(30, 400);
    }
}

void MainWindow::paint()
{
    /* Открываем документ с планом
     * Переходим к главному тегу <plan>
     * */
    XMLDocument doc;
    doc.LoadFile(fileNameChar);
    XMLElement *plan = doc.FirstChildElement("plan");

    QVector <QPoint> dots;

    /* Устанавливаем размер сцены
     * */
    scene->setSceneRect(0,0, 1000, 600);
    //scene->setBackgroundBrush(QBrush(Qt::CrossPattern));

    /* Проходим по каждой ветке, считывая всю необходимую информацию
     * и добавляя элементы на сцену в качестве полигонов
     * */
    XMLElement *xml_wall = plan->FirstChildElement("wall");
    while(xml_wall != nullptr)
    {
        XMLElement *xml_dot = xml_wall->FirstChildElement("dot");
        while(xml_dot != nullptr)
        {
            QPoint temp;
            temp.setX(atoi(xml_dot->Attribute("x")));
            temp.setY(atoi(xml_dot->Attribute("y")));
            dots.push_back(temp);
            xml_dot = xml_dot->NextSiblingElement("dot");
        }
        dots.push_back(dots[0]);
        QPolygonF pol(dots);
        scene->addPolygon(pol, QPen(Qt::black), QBrush(Qt::darkYellow));

        xml_wall = xml_wall->NextSiblingElement("wall");
        dots.clear();
    }

    XMLElement *xml_win = plan->FirstChildElement("window");
    while(xml_win != nullptr)
    {
        XMLElement *xml_dot = xml_win->FirstChildElement("dot");
        while(xml_dot != nullptr)
        {
            QPoint temp;
            temp.setX(atoi(xml_dot->Attribute("x")));
            temp.setY(atoi(xml_dot->Attribute("y")));
            dots.push_back(temp);
            xml_dot = xml_dot->NextSiblingElement("dot");
        }
        dots.push_back(dots[0]);
        QPolygonF pol(dots);
        scene->addPolygon(pol, QPen(Qt::black), QBrush(Qt::darkBlue));

        xml_win = xml_win->NextSiblingElement("window");
        dots.clear();
    }

    XMLElement *xml_door = plan->FirstChildElement("door");
    while(xml_door != nullptr)
    {
        XMLElement *xml_dot = xml_door->FirstChildElement("dot");
        while(xml_dot != nullptr)
        {
            QPoint temp;
            temp.setX(atoi(xml_dot->Attribute("x")));
            temp.setY(atoi(xml_dot->Attribute("y")));
            dots.push_back(temp);
            xml_dot = xml_dot->NextSiblingElement("dot");
        }
        dots.push_back(dots[0]);
        QPolygonF pol(dots);
        scene->addPolygon(pol, QPen(Qt::black), QBrush(Qt::darkYellow));

        xml_door = xml_door->NextSiblingElement("door");
        dots.clear();
    }
}

void MainWindow::on_tempBut_clicked()
{
    /* Чистим сцену от старых данных (если они были)
     * Открываем файл и отрисовываем сцену в функции paint()
     * */
    scene->clear();

    fileName = QFileDialog::getOpenFileName(nullptr, tr("Open File"), "", tr("XML (*.xml)"));
    tmp = fileName.toLocal8Bit();
    fileNameChar = tmp.data();

    ui->TPlan->setScene(scene);
    paint();

    ui->choseobjBut->setEnabled(true);
    ui->countBut->setEnabled(true);
    ui->createlistBut->setEnabled(true);
    ui->areaBut->setEnabled(true);
    ui->scaleEdit->setEnabled(true);
    ui->scaleLabel->setEnabled(true);
    ui->scaleLabel_2->setEnabled(true);
    ui->scaleLabel_3->setEnabled(true);
    ui->autoplacement->setEnabled(true);
    ui->areaLine->setText("");
}

void MainWindow::on_autoplacement_clicked()
{
    foreach(TComp *comp, comps)
    {

        comp->setPos(randomBetween(30, 900), randomBetween(30, 400));
        qreal pos_x = randomBetween(30, 900);
        qreal pos_y = randomBetween(30, 400);

        while(!scene->collidingItems(comp).isEmpty())
        {
            comp->setX(pos_x);
            comp->setY(pos_y);
            pos_x = randomBetween(30, 900);
            pos_y = randomBetween(30, 400);
        }
    }
    foreach(TPrinter *printer, printers)
    {
        printer->setPos(randomBetween(30, 900), randomBetween(30, 400));
        qreal pos_x = randomBetween(30, 900);
        qreal pos_y = randomBetween(30, 400);

        while(!scene->collidingItems(printer).isEmpty())
        {
            printer->setX(pos_x);
            printer->setY(pos_y);
            pos_x = randomBetween(30, 900);
            pos_y = randomBetween(30, 400);
        }
    }
    foreach(TRouter *router, routers)
    {
        router->setPos(randomBetween(30, 900), randomBetween(30, 400));
        qreal pos_x = randomBetween(30, 900);
        qreal pos_y = randomBetween(30, 400);

        while(!scene->collidingItems(router).isEmpty())
        {
            router->setX(pos_x);
            router->setY(pos_y);
            pos_x = randomBetween(30, 900);
            pos_y = randomBetween(30, 400);
        }
    }
    foreach(TCustomObject *cobj, custom_objects)
    {
        auto max_w =  scene->width() - cobj->polygon->boundingRect().width() - 100;
        auto max_h = scene->height() - cobj->polygon->boundingRect().height() - 100;
        qreal pos_x = randomBetween(30, max_w);
        qreal pos_y = randomBetween(30, max_h);

        cobj->setPos(pos_x, pos_y);

        while(!scene->collidingItems(cobj).isEmpty())
        {
            pos_x = randomBetween(30, max_w);
            pos_y = randomBetween(30, max_h);
            cobj->setPos(pos_x, pos_y);
        }
        cobj->update();
    }
}

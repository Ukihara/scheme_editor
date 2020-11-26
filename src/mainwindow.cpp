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
    this->resize(1200, 700);
    this->setFixedSize(1200, 700);
    scene = new QGraphicsScene(this);

    //инициализируем окно выбора и подключаем к слоту
    //возврата на главное окно кнопку "Готово" на втором окне
    choseobj = new ChoseObj();
    connect(choseobj, &ChoseObj::firstWindow, this, &MainWindow::show);
    connect(choseobj, &ChoseObj::firstWindow_comp, this, &MainWindow::paint_comp);
    connect(choseobj, &ChoseObj::firstWindow_prin, this, &MainWindow::paint_prin);
    connect(choseobj, &ChoseObj::firstWindow_rout, this, &MainWindow::paint_rout);

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
    ui->countLine->setText("Вы нажали кнопку");
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
    item->setPos(randomBetween(30, 470), randomBetween(30, 470));
    comps.push_back(item);
    scene->addItem(item);
}

void MainWindow::paint_prin()
{
    TPrinter *item = new TPrinter();
    item->setPos(randomBetween(30, 470), randomBetween(30, 470));
    printers.push_back(item);
    scene->addItem(item);
}

void MainWindow::paint_rout()
{
    TRouter *item = new TRouter();
    item->setPos(randomBetween(30, 470), randomBetween(30, 470));
    routers.push_back(item);
    scene->addItem(item);
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
        scene->addPolygon(pol, QPen(Qt::black), QBrush(Qt::darkYellow));

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
}



#include "mainwindow.h"
#include "ui_mainwindow.h"

QString fileName;
const char *fileNameChar = "";
QByteArray tmp;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);

    //инициализируем окно выбора и подключаем к слоту
    //возврата на главное окно кнопку "Готово" на втором окне
    choseobj = new ChoseObj();
    connect(choseobj, &ChoseObj::firstWindow, this, &MainWindow::show);

    createlist = new CreateList();
    connect(createlist, &CreateList::firstWindow, this, &MainWindow::show);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_choseobjBut_clicked()
{
    choseobj->show();
    this->close();
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
    ui->areaLine->setText("Вы нажали кнопку");
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
}



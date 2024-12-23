#include "printgraf.h"
#include "ui_printgraf.h"
#include "qcustomplot.h"

printGraf::printGraf(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::printGraf)
{
    ui->setupUi(this);

    ui->widget_2->plotLayout()->insertRow(0);
    ui->widget_2->plotLayout()->addElement(0,0,
    new QCPPlotTitle(ui->widget_2,"График выручки"));

    QVector <double> dx, dy;
    double minX, minY, maxX, maxY;


    minX = 0;
    minY = 0;
    maxX = 0;
    maxY = 0;
    QSqlQuery *query = new QSqlQuery();

    if (query->exec("SELECT * FROM chart"))
    {
        while (query->next())
        {
            //Поиск максимального и минимального значения координат
            if (minX>=query->value(0).toDouble())
              minX = query->value(0).toDouble();
            if (minY>=query->value(1).toDouble())
              minY = query->value(1).toDouble();
            if (maxX<=query->value(0).toDouble())
              maxX = query->value(0).toDouble();
            if (maxY<=query->value(1).toDouble())
              maxY = query->value(1).toDouble();
            //Добавление координат в вектора
            dx << query->value(0).toDouble();
            dy << query->value(1).toDouble();
        }
        //Создание объекта с привязкой к осям виджета
        QCPBars *bar = new QCPBars(ui->widget_2->xAxis,
                                   ui->widget_2->yAxis);
        bar->setName("Значение");

    //Цвет заливки графика (R,G,B,Transparency)
    bar->setBrush(QColor(255,0,0,255));
    bar->setData(dx,dy); //координаты точек
    bar->setWidth(0.25); //толщина линий
    //Добавление подписей осей
    ui->widget_2->xAxis->setLabel("Месяц");
    ui->widget_2->yAxis->setLabel("Выручка");
    //Установка границ отображения графика
    ui->widget_2->xAxis->setRange(minX,maxX+0.20);
    ui->widget_2->yAxis->setRange(minY,maxY+1);
    //Запрет автоматического определения шага шкалы
    ui->widget_2->xAxis->setAutoTickStep(false);
    ui->widget_2->yAxis->setAutoTickStep(false);
    //Ручная установка шага
    ui->widget_2->xAxis->setTickStep(1);
    ui->widget_2->yAxis->setTickStep(1);
    }

}

printGraf::~printGraf()
{
    delete ui;
}

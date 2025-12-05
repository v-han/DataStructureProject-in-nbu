#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    addPoint();
    drawPoint();

    connect(ui->StartButton,&QPushButton::clicked,this,[this]{PathSearch();});
}

Widget::~Widget()
{
    delete ui;
}

void Widget::addPoint()
{
    graph.addPoint(ui->BeginPoint,ui->EndPoint);
}

void Widget::drawPoint()
{
    graph.drawPoint(Scene);
    ui->graphicsView->setScene(Scene);
}

void Widget::PathSearch()
{
    graph.drawPoint(Scene);
    graph.PathSearch(ui->BeginPoint, ui->EndPoint, ui->textBrowserPath, ui->textBrowserLong, Scene);
    ui->graphicsView->setScene(Scene);
}

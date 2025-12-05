#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->pushButton,&QPushButton::clicked,this,[this](){StartSort();});
}

Widget::~Widget()
{
    delete ui;
}

void Widget::StartSort()
{
    sort.StartSort(ui->textBrowser,ui->spinBox);
}

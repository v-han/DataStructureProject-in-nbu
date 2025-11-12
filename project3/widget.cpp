#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //画迷宫按钮绑定
    QList<QPushButton*> buttons;
    for (int i = 2; i <= 80; i++)
    {
        // 查找按钮
        QPushButton* button = nullptr;
        if (i <= 9)
            button = findChild<QPushButton*>(QString("Button0%1").arg(i));
        else
            button = findChild<QPushButton*>(QString("Button%1").arg(i));
        if (button)
            buttons.append(button);
    }

    for (QPushButton* button : buttons)
    {
        connect(button, &QPushButton::clicked, this, [this, button]() {
            ChangeButton(button);
        });
    }

    connect(ui->StartButton, &QPushButton::clicked, this, [this]() {
            // 每次开始前先重置上一次的“走过”标记
            Reflesh();
            MoveMaze(0, 0);
        });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::Reflesh()
{
    for (int i = 0;i < 9;i++)
    {
        for (int j = 0;j < 9;j++)
        {
            QPushButton* button = PosToButton(i,j);
            char info = Maze.GetInfo(i,j);
            if (info == 'i' || info == 'o' || info == 'd')
            {
                button->setStyleSheet("QPushButton {background-color: white;color: black;}");
                if (info == 'd')
                    button->setText("空");
            }
        }      
    }
    Maze.Reset();
}

void Widget::ChangeButton(QPushButton* button)  //改变按钮的属性
{
    QString str = button->objectName();//Button01
    int Number = str[6].digitValue()*10 + str[7].digitValue();
    int posI = Number / 9;
    int posJ = Number % 9 - 1;

    if(Maze.GetInfo(posI,posJ) == 'e')
    {
        button->setText("墙");
        button->setStyleSheet("QPushButton {background-color: black;color: white;}");
        Maze.SetInfo(posI,posJ,'q');
    }
    else
    {
        button->setText("空");
        button->setStyleSheet("QPushButton {background-color: white;color: black;}");
        Maze.SetInfo(posI,posJ,'e');
    }
}

QPushButton* Widget::PosToButton(int posI, int posJ)
{
    int Number = posI * 9 + posJ + 1;
    QPushButton* button = nullptr;
    if (Number <= 9)
        button = findChild<QPushButton*>(QString("Button0%1").arg(Number));
    else
        button = findChild<QPushButton*>(QString("Button%1").arg(Number));
    return button;
}

bool Widget::MoveMaze(int posI, int posJ)
{
    // 到达终点
    if (posI == 8 && posJ == 8)
    {
        QPushButton* button = PosToButton(posI, posJ);
        button->setStyleSheet("QPushButton {background-color: green; color: white;}");
        return true;
    }

    // 当前格子标记为已走过
    Maze.SetInfo(posI, posJ, 'd');
    QPushButton* curButton = PosToButton(posI, posJ);
    if (curButton)
        curButton->setText("走");

    // 四个方向：下、右、上、左
    const int dx[4] = {1, 0, -1, 0};
    const int dy[4] = {0, 1, 0, -1};

    for (int k = 0; k < 4; ++k)
    {
        int ni = posI + dx[k];
        int nj = posJ + dy[k];

        if (ni < 0 || ni >= 9 || nj < 0 || nj >= 9)
            continue;

        char cell = Maze.GetInfo(ni, nj);
        if (cell == 'e' || cell == 'o')
        {
            if (MoveMaze(ni, nj))
            {
                Maze.SetInfo(posI, posJ, 'd');
                if (curButton)
                {
                    curButton->setText("路径");
                    curButton->setStyleSheet("QPushButton {background-color: lightgreen; color: black;}");
                }
                return true;
            }
        }
    }

    // 回溯
    Maze.SetInfo(posI, posJ, 'e');
    if (curButton)
    {
        curButton->setText("空");
        curButton->setStyleSheet("QPushButton {background-color: white; color: black;}");
    }

    return false;
}

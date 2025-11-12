#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    l = new LinkList();
    ui->setupUi(this);
    ui->length->setText("0");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_add_btn_clicked()
{
    // 输入校验
    QString name = ui->name_input->toPlainText();
    if(name.isEmpty()){
        QMessageBox::critical(this,"错误","未填写姓名");
        return;
    }
    QString birth = ui->birth_input->toPlainText();
    if(birth.isEmpty()){
        QMessageBox::critical(this,"错误","未填写生日");
        return;
    }
    bool ok;
    int insertIndex = ui->index_input->toPlainText().toInt(&ok,10);
    if(!ok){
        QMessageBox::critical(this,"错误","不合法的输入");
        return;
    }

    // 插入操作处理逻辑
    ok = l->addNode(name.toUtf8().toStdString(),birth.toUtf8().toStdString(),insertIndex);
    if(!ok){
        QMessageBox::critical(this,"错误","插入失败");
        return;
    }

    // 后置操作
    QMessageBox::information(this,"成功","插入成功");
    ui->length->setText(QString::number(l->length));
    qDebug().noquote() << l->showLinkList();
}


void MainWindow::on_delete_btn_clicked()
{
    bool ok;
    int deleteIndex = ui->delete_index_input->toPlainText().toInt(&ok,10);
    if(!ok){
        QMessageBox::critical(this,"错误","不合法的输入");
        return;
    }



    ok = l->deleteNode(deleteIndex);
    if(!ok){
        QMessageBox::critical(this,"错误","删除失败");
        return;
    }


    ui->length->setText(QString::number(l->length));
    QMessageBox::information(this,"成功","删除成功");
    qDebug().noquote() << l->showLinkList();
}


void MainWindow::on_find_btn_clicked()
{
    string searchName = ui->search_name->toPlainText().toUtf8().toStdString();
    LNode* p = l->findNode(searchName);
    if(p){
        ui->name_show->setText(QString::fromUtf8(p->val->getName().c_str()));
        ui->birth_show->setText(QString::fromUtf8(p->val->getBirth().c_str()));
        return ;
    }
    QMessageBox::warning(this,"警告","未找到该用户");

}



void MainWindow::on_clear_btn_clicked()
{
    l->clearList();
    ui->length->setText(QString::number(l->length));
}


void MainWindow::on_close_btn_clicked()
{
    this->close();
}


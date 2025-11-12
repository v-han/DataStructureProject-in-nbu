#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "linklist.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_add_btn_clicked();

    void on_delete_btn_clicked();

    void on_find_btn_clicked();

    void on_clear_btn_clicked();

    void on_close_btn_clicked();

private:
    Ui::MainWindow *ui;
    LinkList* l;
};
#endif // MAINWINDOW_H

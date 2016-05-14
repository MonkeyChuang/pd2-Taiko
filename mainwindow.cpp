#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    width_v=800-20;
    height_v=800*0.75-20;

    view=new QGraphicsView(this);
    view->setGeometry(10,10,width_v,height_v);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    taiko=new Taiko(width_v,height_v);
    taiko->setSceneRect(0.0,0.0,width_v,height_v);

    view->setScene(taiko);
    view->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

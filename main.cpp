#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    int width_w=800;
    int height_w=width_w*0.75;
    w.setFixedSize(width_w,height_w);
    w.show();

    return a.exec();
}

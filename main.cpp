#include "mainwindow.h"
#include <QApplication>
#include <QIcon>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    int width_w=800;
    int height_w=width_w*0.75;
    QIcon icon_w(":Pic/pic/0.png");

    w.setGeometry(300,100,width_w,height_w);
    w.setFixedSize(width_w,height_w);
    w.setWindowTitle("Taiko:Drum Master");
    w.setWindowIcon(icon_w);
    w.show();

    return a.exec();
}

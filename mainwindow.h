#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "taiko.h"
#include <QMainWindow>
#include <QGraphicsView>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsView *view;
    int width_v;
    int height_v;
    Taiko *taiko;
};

#endif // MAINWINDOW_H

#ifndef DRUM_H
#define DRUM_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QTimer>
class Drum:public QGraphicsPixmapItem
{
public:
    Drum(int drum_type,int ms);
    void setStart(int ms);
    void drumInitiate(int drum_type);       //d_type = 0,1,2,3
    void ReadyToGo();
    int drumT;

private:
    int start_t;
    QPixmap drum_pic;
    QTimer *clk;
};

#endif // DRUM_H

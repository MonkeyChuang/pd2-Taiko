#include "drum.h"

Drum::Drum(int drum_type, int ms)
{
    setStart(ms);
    drumInitiate(drum_type);
    clk = new QTimer;
    clk->setSingleShot(true);
}
void Drum::setStart(int ms)
{
    start_t=ms;
}
void Drum::drumInitiate(int drum_type)
{
    drumT=drum_type;
    if(drum_type == 0)
    {
        drum_pic.load(":Pic/pic/0.png");
        this->setPixmap(drum_pic);
        this->setScale(1.25);
        this->setPos(778,152);
    }
    else if(drum_type == 1)
    {
        drum_pic.load(":Pic/pic/1.png");
        this->setPixmap(drum_pic);
        this->setScale(1.25);
        this->setPos(778,152);
    }
    else if(drum_type == 2)
    {
        drum_pic.load(":Pic/pic/2.png");
        this->setPixmap(drum_pic);
        this->setScale(1.2);
        this->setPos(55,139);
    }
    else if(drum_type == 3)
    {
        drum_pic.load(":Pic/pic/3.png");
        this->setPixmap(drum_pic);
        this->setScale(1.2);
        this->setPos(778,139);
    }
}
void Drum::ReadyToGo()
{
    clk->start(start_t);
}

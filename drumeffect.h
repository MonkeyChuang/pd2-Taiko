#ifndef DRUMEFFECT_H
#define DRUMEFFECT_H
#include <QGraphicsPixmapItem>
class DrumEffect:public QGraphicsPixmapItem
{
public:
    DrumEffect();
    void VisibleOn();
    void VisibleOff();
};

#endif // DRUMEFFECT_H

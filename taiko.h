#ifndef TAIKO_H
#define TAIKO_H

#include "drumeffect.h"
#include "drum.h"

#include <QGraphicsScene>
#include <QPushButton>
#include <QRect>
#include <QPixmap>
#include <QBrush>
#include <QGraphicsProxyWidget>
#include <QKeyEvent>
#include <QTimer>
#include <QProgressBar>
#include <QTimeLine>
#include <QGraphicsPixmapItem>
#include <QPointF>
#include <ctime>
#include <QSound>
class Taiko:public QGraphicsScene
{
Q_OBJECT
public:
    Taiko(int width_v,int height_v);
    void setBg(int screenMode);
private:
    int width_s;
    int height_s;
    bool mainP_IsInit,gameP_IsInit;
    QRect *rect_s;
    QPixmap bg_pic;
    QBrush *br;
    QPushButton *start_b,*exit_b;
    QGraphicsProxyWidget *str,*ext,*elpT;
    QSound *readygo,*red,*blue;

    QPixmap drumCover_pic,redEffect_pic,blueEffect_pic,drum_pic;
    QTimeLine *game_clk;
    QProgressBar *elpsTime;
    QGraphicsPixmapItem *drum_cover;
    DrumEffect *red_effect,*blue_effect;
    Drum *drum1,*drum2,*drum3,*drum4;
    QTimer *move_clk;
    QPointF move_delta,ini_pos1,ini_pos2,ini_pos3,ini_pos4;
    void drumBuild();

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
signals:
    void Effect_Type_On(int e_type);
    void Effect_Type_Off(int e_type);
private slots:
    void mainP_ctor();
    void mainP_dtor();
    void gameP_ctor();
    void gameP_dtor();

    void Visible_On(int e_type);
    void Visible_Off(int e_type);

    void drum_move();
};

#endif // TAIKO_H

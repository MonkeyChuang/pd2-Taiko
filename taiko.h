#ifndef TAIKO_H
#define TAIKO_H

#include "drumeffect.h"
#include "drum.h"
#include "dialog.h"

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
#include <QLCDNumber>

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
    QGraphicsProxyWidget *str,*ext;

    QSound *readygo,*red,*blue,*gameover;

    QPixmap drumCover_pic,redEffect_L_pic,blueEffect_L_pic,redEffect_R_pic,blueEffect_R_pic,drum_pic;
    QGraphicsProxyWidget *elpT,*scMoni;
    QTimeLine *game_clk;
    QProgressBar *elpsTime;
    QGraphicsPixmapItem *drum_cover;
    DrumEffect *red_effect_L,*blue_effect_L,*red_effect_R,*blue_effect_R;
    Drum *drum1,*drum2,*drum3,*drum4;
    QTimer *move_clk;
    QPointF move_delta,ini_pos1,ini_pos2,ini_pos3,ini_pos4;
    void drumBuild();
    int score;
    Dialog *dlg;         // l: lower case of 'L'
    QLCDNumber *ScoreMoni;
protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
signals:
    void Effect_Type_On(int e_type);
    void Effect_Type_Off(int e_type);
    void scoreChanged(int sco);
    void sendScore(int sco);
private slots:
    void mainP_ctor();
    void mainP_dtor();
    void gameP_ctor();
    void gameP_dtor();

    void Visible_On(int e_type);
    void Visible_Off(int e_type);
    void addScore(int typeSc);
    void sendScore_s();
    void drum_move();
};

#endif // TAIKO_H

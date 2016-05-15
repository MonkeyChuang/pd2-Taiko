#include "taiko.h"
#include <QApplication>
#include <QFont>
Taiko::Taiko(int width_v,int height_v)
{        
    width_s=width_v;
    height_s=height_v;
    rect_s = new QRect(0,0,width_s,height_s);

    move_delta.setX(-2.0);


    srand(time(NULL));
    readygo = new QSound(":Sound/sound/readygo.wav");
    red = new QSound(":Sound/sound/red.wav");
    blue = new QSound(":Sound/sound/blue.wav");
    gameover = new QSound(":Sound/sound/gameover.wav");
    mainP_IsInit=false;
    gameP_IsInit=false;
    mainP_ctor();

}
void Taiko::setBg(int screenMode)
{
    if(screenMode == 1)
    {
        bg_pic.load(":Pic/pic/main_bg.jpg");
        bg_pic=bg_pic.scaled(rect_s->size());
        br = new QBrush(bg_pic);
        this->setBackgroundBrush(*br);

    }
    else if(screenMode == 2)
    {
        bg_pic.load(":Pic/pic/game_bg.jpg");
        bg_pic=bg_pic.scaled(rect_s->size());
        br = new QBrush(bg_pic);
        this->setBackgroundBrush(*br);
    }
    delete br;
}
void Taiko::mainP_ctor()
{
    setBg(1);
    if(!mainP_IsInit)
    {
        QFont f("Cursive",20,20);
        start_b = new QPushButton("Start");
        exit_b = new QPushButton("Exit");
        start_b->setFont(f);
        exit_b->setFont(f);
        start_b->setGeometry(width_s/2-100,3*height_s/4,200,40);
        exit_b->setGeometry(width_s/2-100,3*height_s/4+60,200,40);

        connect(start_b,SIGNAL(clicked()),readygo,SLOT(play()));
        connect(start_b,SIGNAL(clicked()),this,SLOT(gameP_ctor()));
        connect(exit_b,SIGNAL(clicked()),QApplication::instance(),SLOT(quit()));
        connect(start_b,SIGNAL(clicked()),this,SLOT(mainP_dtor()));

    }
    str=addWidget(start_b);
    ext=addWidget(exit_b);
}
void Taiko::mainP_dtor()
{
    mainP_IsInit=false;
    removeItem(str);
    removeItem(ext);
    disconnect(start_b,SIGNAL(clicked()),readygo,SLOT(play()));
    disconnect(start_b,SIGNAL(clicked()),this,SLOT(gameP_ctor()));
    disconnect(exit_b,SIGNAL(clicked()),QApplication::instance(),SLOT(quit()));
    disconnect(start_b,SIGNAL(clicked()),this,SLOT(mainP_dtor()));

}
void Taiko::gameP_ctor()
{
    setBg(2);
    if(!gameP_IsInit)
    {
        ini_pos1.setX(778.0);
        ini_pos1.setY(152.0);
        ini_pos2.setY(152.0);
        ini_pos3.setY(152.0);
        ini_pos4.setY(152.0);
        ini_pos2.setX((778.0+175.0));
        ini_pos3.setX(778.0+350.0);
        ini_pos4.setX(778.0+432.0);

        move_clk = new QTimer;
        drumBuild();

        score=0;
        ScoreMoni = new QLCDNumber;
        ScoreMoni->setGeometry(10,10,100,50);
//        ScoreMoni->setSegmentStyle(QLCDNumber::Flat);
        scMoni=addWidget(ScoreMoni);
        ScoreMoni->display(score);

        drumCover_pic.load(":Pic/pic/drum_cover.png");
        drum_cover = new QGraphicsPixmapItem(drumCover_pic);
        drum_cover->setScale(width_s/1024.0);
        drum_cover->setPos(0,122);
        addItem(drum_cover);

        redEffect_L_pic.load(":Pic/pic/click_effect_red_left.png");
        red_effect_L = new DrumEffect;
        red_effect_L->setPixmap(redEffect_L_pic);
        red_effect_L->setScale(0.7);
        red_effect_L->setPos(22,140);
        addItem(red_effect_L);

        redEffect_R_pic.load(":Pic/pic/click_effect_red_right.png");
        red_effect_R = new DrumEffect;
        red_effect_R->setPixmap(redEffect_R_pic);
        red_effect_R->setScale(0.7);
        red_effect_R->setPos(24,140);
        addItem(red_effect_R);


        blueEffect_L_pic.load(":Pic/pic/click_effect_blue_left.png");
        blue_effect_L= new DrumEffect;
        blue_effect_L->setPixmap(blueEffect_L_pic);
        blue_effect_L->setScale(0.8);
        blue_effect_L->setPos(6,125);
        addItem(blue_effect_L);

        blueEffect_R_pic.load(":Pic/pic/click_effect_blue_right.png");
        blue_effect_R= new DrumEffect;
        blue_effect_R->setPixmap(blueEffect_R_pic);
        blue_effect_R->setScale(0.8);
        blue_effect_R->setPos(6,125);
        addItem(blue_effect_R);

        elpsTime = new QProgressBar;
        elpsTime->setGeometry(334,30,380,30);
        elpsTime->setRange(0,100);
        elpT=addWidget(elpsTime);

        game_clk = new QTimeLine(30*1000);
        game_clk->setFrameRange(0,100);

        dlg = new Dialog;
        //need to be modified
        connect(this,SIGNAL(scoreChanged(int)),ScoreMoni,SLOT(display(int)));

        connect(game_clk,SIGNAL(frameChanged(int)),elpsTime,SLOT(setValue(int)));
        connect(this,SIGNAL(Effect_Type_On(int)),this,SLOT(Visible_On(int)));
        connect(this,SIGNAL(Effect_Type_Off(int)),this,SLOT(Visible_Off(int)));
        connect(move_clk,SIGNAL(timeout()),this,SLOT(drum_move()));

        connect(game_clk,SIGNAL(finished()),gameover,SLOT(play()));
        connect(game_clk,SIGNAL(finished()),this,SLOT(sendScore_s()));
        connect(this,SIGNAL(sendScore(int)),dlg,SLOT(getScore(int)));
        connect(game_clk,SIGNAL(finished()),move_clk,SLOT(stop()));
        connect(game_clk,SIGNAL(finished()),dlg,SLOT(exec()));

        connect(dlg,SIGNAL(playagain()),readygo, SLOT(play()));
        connect(dlg,SIGNAL(gomenu()),this,SLOT(mainP_ctor()));
        connect(dlg,SIGNAL(accepted()),this, SLOT(gameP_dtor()));
        connect(dlg,SIGNAL(playagain()),this, SLOT(gameP_ctor()));
        connect(dlg,SIGNAL(exitgame()),QApplication::instance(),SLOT(quit()));


        move_clk->start(8);
        game_clk->start();
    }

}
void Taiko::gameP_dtor()
{
    score=0;
    disconnect(game_clk,SIGNAL(frameChanged(int)),elpsTime,SLOT(setValue(int)));
    disconnect(this,SIGNAL(Effect_Type_On(int)),this,SLOT(Visible_On(int)));
    disconnect(this,SIGNAL(Effect_Type_Off(int)),this,SLOT(Visible_Off(int)));
    disconnect(move_clk,SIGNAL(timeout()),this,SLOT(drum_move()));
    disconnect(game_clk,SIGNAL(finished()),dlg,SLOT(exec()));
    disconnect(this,SIGNAL(scoreChanged(int)),ScoreMoni,SLOT(display(int)));

    delete game_clk;
    delete move_clk;
    removeItem(elpT);
    removeItem(scMoni);
    removeItem(drum_cover);
    removeItem(red_effect_L);
    removeItem(red_effect_R);
    removeItem(blue_effect_L);
    removeItem(blue_effect_R);
    removeItem(drum1);
    removeItem(drum2);
    removeItem(drum3);
    removeItem(drum4);
}
void Taiko::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Q)
    {
        gameP_dtor();
        mainP_ctor();
    }
    else if(event->key() == Qt::Key_R)
    {
        gameP_dtor();
        gameP_ctor();
    }
    else if(event->key() == Qt::Key_F)
    {
        emit Effect_Type_On(1);
        if(drum1->drumT == 0 && drum1->x() < 218 && drum1->x() > 90)
        {
            if(drum1->x() < 178.0 && drum1->x() > 151.0)
            {
                addScore(2);
                drum1->setOpacity(0.0);
                red->play();
            }
            else
            {
                addScore(1);
                drum1->setOpacity(0.0);
                red->play();
            }
        }

        if(drum2->drumT == 0 && drum2->x() < 218 && drum2->x() > 90)
        {
            if(drum2->x() < 178.0 && drum2->x() > 151.0)
            {
                addScore(2);
                drum2->setOpacity(0.0);
                red->play();
            }
            else
            {
                addScore(1);
                drum2->setOpacity(0.0);
                red->play();
            }
        }
        if(drum3->drumT == 0 && drum3->x() < 218 && drum3->x() > 90)
        {
            if(drum3->x() < 178.0 && drum3->x() > 151.0)
            {
                addScore(2);
                drum3->setOpacity(0.0);
                red->play();
            }
            else
            {
                addScore(1);
                drum3->setOpacity(0.0);
                red->play();
            }
        }
        if(drum4->drumT == 0 && drum4->x() < 218 && drum4->x() > 90)
        {
            if(drum4->x() < 178.0 && drum4->x() > 151.0)
            {
                addScore(2);
                drum4->setOpacity(0.0);
                red->play();
            }
            else
            {
                addScore(1);
                drum4->setOpacity(0.0);
                red->play();
            }
        }
    }
    else if(event->key() == Qt::Key_J)
    {
        emit Effect_Type_On(3);
        if(drum1->drumT == 0 && drum1->x() < 218 && drum1->x() > 90)
        {
            if(drum1->x() < 178.0 && drum1->x() > 151.0)
            {
                addScore(2);
                drum1->setOpacity(0.0);
                red->play();
            }
            else
            {
                addScore(1);
                drum1->setOpacity(0.0);
                red->play();
            }
        }

        if(drum2->drumT == 0 && drum2->x() < 218 && drum2->x() > 90)
        {
            if(drum2->x() < 178.0 && drum2->x() > 151.0)
            {
                addScore(2);
                drum2->setOpacity(0.0);
                red->play();
            }
            else
            {
                addScore(1);
                drum2->setOpacity(0.0);
                red->play();
            }
        }
        if(drum3->drumT == 0 && drum3->x() < 218 && drum3->x() > 90)
        {
            if(drum3->x() < 178.0 && drum3->x() > 151.0)
            {
                addScore(2);
                drum3->setOpacity(0.0);
                red->play();
            }
            else
            {
                addScore(1);
                drum3->setOpacity(0.0);
                red->play();
            }
        }
        if(drum4->drumT == 0 && drum4->x() < 218 && drum4->x() > 90)
        {
            if(drum4->x() < 178.0 && drum4->x() > 151.0)
            {
                addScore(2);
                drum4->setOpacity(0.0);
                red->play();
            }
            else
            {
                addScore(1);
                drum4->setOpacity(0.0);
                red->play();
            }
        }
    }
    else if(event->key() == Qt::Key_D)
    {
        emit Effect_Type_On(2);
        if(drum1->drumT == 1 && drum1->x() < 218 && drum1->x() > 90)
        {
            if(drum1->x() < 178.0 && drum1->x() > 151.0)
            {
                addScore(2);
                drum1->setOpacity(0.0);
                blue->play();
            }
            else
            {
                addScore(1);
                drum1->setOpacity(0.0);
                blue->play();
            }
        }

        if(drum2->drumT == 1 && drum2->x() < 218 && drum2->x() > 90)
        {
            if(drum2->x() < 178.0 && drum2->x() > 151.0)
            {
                addScore(2);
                drum2->setOpacity(0.0);
                blue->play();
            }
            else
            {
                addScore(1);
                drum2->setOpacity(0.0);
                blue->play();
            }
        }
        if(drum3->drumT == 1 && drum3->x() < 218 && drum3->x() > 90)
        {
            if(drum3->x() < 178.0 && drum3->x() > 151.0)
            {
                addScore(2);
                drum3->setOpacity(0.0);
                blue->play();
            }
            else
            {
                addScore(1);
                drum3->setOpacity(0.0);
                blue->play();
            }
        }
        if(drum4->drumT == 1 && drum4->x() < 218 && drum4->x() > 90)
        {
            if(drum4->x() < 178.0 && drum4->x() > 151.0)
            {
                addScore(2);
                drum4->setOpacity(0.0);
                blue->play();
            }
            else
            {
                addScore(1);
                drum4->setOpacity(0.0);
                blue->play();
            }
        }
    }
    else if(event->key() == Qt::Key_K)
    {
        emit Effect_Type_On(4);
        if(drum1->drumT == 1 && drum1->x() < 218 && drum1->x() > 90)
        {
            if(drum1->x() < 178.0 && drum1->x() > 151.0)
            {
                addScore(2);
                drum1->setOpacity(0.0);
                blue->play();
            }
            else
            {
                addScore(1);
                drum1->setOpacity(0.0);
                blue->play();
            }
        }

        if(drum2->drumT == 1 && drum2->x() < 218 && drum2->x() > 90)
        {
            if(drum2->x() < 178.0 && drum2->x() > 151.0)
            {
                addScore(2);
                drum2->setOpacity(0.0);
                blue->play();
            }
            else
            {
                addScore(1);
                drum2->setOpacity(0.0);
                blue->play();
            }
        }
        if(drum3->drumT == 1 && drum3->x() < 218 && drum3->x() > 90)
        {
            if(drum3->x() < 178.0 && drum3->x() > 151.0)
            {
                addScore(2);
                drum3->setOpacity(0.0);
                blue->play();
            }
            else
            {
                addScore(1);
                drum3->setOpacity(0.0);
                blue->play();
            }
        }
        if(drum4->drumT == 1 && drum4->x() < 218 && drum4->x() > 90)
        {
            if(drum4->x() < 178.0 && drum4->x() > 151.0)
            {
                addScore(2);
                drum4->setOpacity(0.0);
                blue->play();
            }
            else
            {
                addScore(1);
                drum4->setOpacity(0.0);
                blue->play();
            }
        }
    }
}
void Taiko::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_F)
    {
        emit Effect_Type_Off(1);
    }
    else if(event->key() == Qt::Key_D)
    {
        emit Effect_Type_Off(2);
    }
    else if(event->key() == Qt::Key_J)
    {
        emit Effect_Type_Off(3);
    }
    else if(event->key() == Qt::Key_K)
    {
        emit Effect_Type_Off(4);
    }
}
void Taiko::addScore(int typeSc)
{
    if(typeSc == 2)
    {
        score+=10;
        emit scoreChanged(score);
    }
    else if(typeSc == 1)
    {
        score+=5;
        emit scoreChanged(score);
    }
}
void Taiko::sendScore_s()
{
    emit sendScore(score);
}

void Taiko::Visible_On(int e_type)
{
    if(e_type == 1)
        red_effect_L->VisibleOn();
    else if(e_type == 2)
        blue_effect_L->VisibleOn();
    else if(e_type == 3)
        red_effect_R->VisibleOn();
    else if(e_type == 4)
        blue_effect_R->VisibleOn();
}
void Taiko::Visible_Off(int e_type)
{
    if(e_type == 1)
        red_effect_L->VisibleOff();
    else if(e_type == 2)
        blue_effect_L->VisibleOff();
    else if(e_type == 3)
        red_effect_R->VisibleOff();
    else if(e_type == 4)
        blue_effect_R->VisibleOff();
}
void Taiko::drum_move()
{
    ini_pos1+=move_delta;
    ini_pos2+=move_delta;
    ini_pos3+=move_delta;
    ini_pos4+=move_delta;

    if(ini_pos1.x() < 80.0)
    {
        drum1->setOpacity(1.0);
        ini_pos1.setX(778.0);
        drum1->drumInitiate(rand()%2);
    }
    if(ini_pos2.x() < 80.0)
    {
        drum2->setOpacity(1.0);
        ini_pos2.setX(778.0);
        drum2->drumInitiate(rand()%2);
    }
    if(ini_pos3.x() < 80.0)
    {
        drum3->setOpacity(1.0);
        ini_pos3.setX(778.0);
        drum3->drumInitiate(rand()%2);
    }
    if(ini_pos4.x() < 80.0)
    {
        drum4->setOpacity(1.0);
        ini_pos4.setX(778.0);
        drum4->drumInitiate(rand()%2);
    }
    drum1->setPos(ini_pos1);
    drum2->setPos(ini_pos2);
    drum3->setPos(ini_pos3);
    drum4->setPos(ini_pos4);

}
void Taiko::drumBuild()
{
    drum1 =new Drum(0,3*1000);
    drum2 =new Drum(1,3*1000);
    drum3 =new Drum(1,3*1000);
    drum4 =new Drum(0,3*1000);

    drum2->setPos(778.0+175.0,0.0);
    drum3->setPos(778.0+350.0,0.0);
    drum4->setPos(778.0+432.0,0.0);

    addItem(drum1);
    addItem(drum2);
    addItem(drum3);
    addItem(drum4);
}

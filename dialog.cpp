#include "dialog.h"
#include <QString>
#include <QFont>
Dialog::Dialog()
{
    setWindowTitle("Ranking Page");
    setGeometry(500,200,400,400);


    restart = new QPushButton("Restart",this);
    main = new QPushButton("Back To Menu",this);
    exit = new QPushButton("Exit",this);

    restart->setGeometry(10,300,100,50);
    main->setGeometry(125,300,150,50);
    exit->setGeometry(290,300,100,50);

    connect(restart,SIGNAL(clicked()),this,SLOT(playAgain()));
    connect(main,SIGNAL(clicked()),this,SLOT(goMenu()));
    connect(exit,SIGNAL(clicked()),this,SLOT(exitGame()));
}
void Dialog::playAgain()
{
    this->accept();
    emit playagain();
}
void Dialog::goMenu()
{
    this->accept();
    emit gomenu();
}
void Dialog::exitGame()
{
    this->reject();
    emit exitgame();
}
void Dialog::getScore(int sc)
{
    score=sc;
    QFont f_t("Cursive",30,20),f_s("Serif",70,50);
    score_t=QString::number(score);

    display_t = new QLabel(this);
    display_s = new QLabel(this);

    display_t->setText(text);
    display_t->setFont(f_t);
    display_t->setGeometry(30,50,200,50);
    display_s->setText(score_t);
    display_s->setFont(f_s);
    display_s->setGeometry(130,130,200,100);
}

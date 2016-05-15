#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QString>

class Dialog : public QDialog
{
    Q_OBJECT
public:
    Dialog();

private:
    int score;
    QString score_t,text="Your Score :";
    QLabel *display_t,*display_s;
    QPushButton *restart,*main,*exit;
signals:
    void playagain();
    void gomenu();
    void exitgame();
private slots:
    void playAgain();
    void goMenu();
    void exitGame();
    void getScore(int sc);
};

#endif // DIALOG_H

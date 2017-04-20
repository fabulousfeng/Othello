#ifndef OTHELLO_H
#define OTHELLO_H

#include "tile.h"
#include <QTimer>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

#include <climits>

#define SIZE 8
#define ONEPLAYER 0
#define TWOPLAYER 1
#define EASY 0
#define HARD 1

class othello{
private:
    static std::set<std::pair<int,int>> next;
    static std::set<std::pair<int,int>> empty_set;

public:
    static QLabel *label;
    static QLabel *score1;
    static QLabel *score2;
    static QLabel *player1;
    static QLabel *player2;
    static QLabel *name1;
    static QLabel *name2;
    static QWidget *myWidget;
    static int turn;
    static bool running;
    static int mode;
    static int difficulty;
    static std::vector<std::vector<Tile*> > tile;

    othello(QWidget *myWidget);
    static void init();
    static void game_update(int x, int y);
    static void update_next();
    static void update_board(int x, int y, bool fade);
    static void show_next(bool show);
    static void score_update();
    static void check_game();
    static void show_turn();
    static void robot_easy();
    static int utility_easy(int x, int y);
    static void robot_hard();

protected:
    static const std::vector<std::pair<int,int>> dirs;

};

class Border // this class will draw the border of the othello game
{
public:
    Border();
    void outline(QWidget *baseWidget, int xPos, int yPos, int Pos)
    {
         QLabel *outLabel = new QLabel(baseWidget);

        if(!Pos)
            outLabel->setGeometry(xPos,yPos,552,20);        //Horizontal Borders, width = 20

        else
            outLabel->setGeometry(xPos,yPos,20,512);        //Vertical Borders, width = 20, 40 is the overlap, so it is 512 here

        outLabel->setStyleSheet("QLabel { background-color :rgb(0, 0, 0); color : black; }"); // set color to be black
    }
};


class Delay: public QObject {
public:
Delay(int duration) {
QTimer::singleShot(duration, this, SLOT(deleteLater()));
}
};

class Fader : public QObject {
public:
Fader(QWidget* target, double start, double end, int fade) {
    auto effect = new QGraphicsOpacityEffect(this);
    target->setGraphicsEffect(effect);

    auto anim = new QPropertyAnimation(effect, "opacity", this);
    connect(anim, &QPropertyAnimation::finished, this, &Fader::deleteLater);
    anim->setDuration(fade);
    anim->setStartValue(start);
    anim->setEndValue(end);
    anim->setEasingCurve(QEasingCurve::OutQuad);
    anim->start();
}

};

#endif // OTHELLO_H

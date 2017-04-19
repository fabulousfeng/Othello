#ifndef OTHELLO_H
#define OTHELLO_H

#include "tile.h"

#define SIZE 8
#define ONEPLAYER 1
#define TWOPLAYER 2
class othello{
private:
    static std::set<std::pair<int,int>> next;
    static std::set<std::pair<int,int>> empty_set;
    static QLabel *score1;
    static QLabel *score2;
public:
    static QWidget *myWidget;
    static int turn;
    static bool running;
    static int mode;
    static std::vector<std::vector<Tile*> > tile;

    static void init();
    static void game_update(int x, int y);
    static void update_next();
    static void update_board(int x, int y);
    static void show_next(bool show);
    static void score_update();
    othello(QWidget *myWidget);

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


#endif // OTHELLO_H

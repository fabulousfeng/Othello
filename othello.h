#ifndef OTHELLO_H
#define OTHELLO_H

#include "tile.h"

#define SIZE 8

class othello{
    QWidget *myWidget;
    static std::set<std::pair<int,int>> next;
    static std::set<std::pair<int,int>> empty_set;
public:
    static std::vector<std::vector<Tile*> > tile;
    static int turn;
    static void game_update(int x, int y);
    static void update_next();
    static void update_board(int x, int y);
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

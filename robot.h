#ifndef ROBOT_H
#define ROBOT_H
#include "tile.h"
#include "othello.h"
#include "othello_widget.h"

class robot{
    std::vector<std::vector<Tile*> > state;
    robot(std::vector<std::vector<Tile*> > s) : state(s){

    }
    std::pair<int,int> minimax_decision();
    int maxValue(std::vector<std::vector<Tile*> > s);
    int minValue(std::vector<std::vector<Tile*> > s);
    void alpha_beta();
};

#endif // ROBOT_H

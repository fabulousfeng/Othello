#ifndef ROBOT_H
#define ROBOT_H
#include "tile.h"
#include "othello.h"
#include "othello_widget.h"

#define DEPTH_HARD 8

#define DEPTH_MEDIUM  4

struct State{
    std::vector<std::vector<Tile*> > board;
    std::set<std::pair<int,int>> next;
    std::set<std::pair<int,int>> empty_set;

};

class robot{
private:
    State initial_state;
    int turn;
    int depth_limit;
    std::pair<int,int> action;

public:

    std::set<std::pair<int, int>> corners = {{0,0},{0,7},{7,0},{7,7}};

    robot(State s_, int depth);
    ~robot();
    std::pair<int,int> alpha_beta_search();
    int maxValue(State s, int alpha, int beta, int depth);
    int minValue(State s, int alpha, int beta, int depth);
    State get_next_state(State current_state, std::pair<int,int> action, int turn);
    int utility(State s);
    int utility_endgame(State s);
    double heuristic(State s);
    int get_mobility(State s, int turn);
};

#endif // ROBOT_H

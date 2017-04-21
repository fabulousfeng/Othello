#include "robot.h"
#include <iostream>
#include <cassert>
extern std::vector<std::vector<int>> weights; // global weights matrix

robot::robot(State s_, int depth) {
    // constructor
    initial_state = s_;
    depth_limit = depth;
    turn = BLACK; // black is the robot(ourself)
    action = std::make_pair(-1, -1); // no action for default
}

std::pair<int,int> robot::alpha_beta_search(){

    if(othello::difficulty == MEDIUM){
        assert(depth_limit == DEPTH_MEDIUM);
    }
    if(othello::difficulty == HARD){
        assert(depth_limit == DEPTH_HARD);
    }
    /***************************************************************************************************
     *                           Alpha_Beta Prunning Search Algorithm
     *
     *  alpha : the best chioce(the highest utility) made by the max node(it is now robot's turn)
     *
     *  beta: the best chioce (the lowest utility) made by the min node(it is now the player's turn)
     *
     ***************************************************************************************************/
    if(this->initial_state.next.empty()) {
        assert(0); // failed
    }
    int alpha = INT_MIN; // assumming the worst case in the beginning
    int beta = INT_MAX;

    // it is our turn, we need to get the action which will max the profit we can get in the future
    auto v = maxValue(this->initial_state, alpha, beta, 0);

//    std::string str = "best:";
//    str += std::to_string(v);
//    QMessageBox::about(othello::myWidget, "me", QString::fromStdString(str));

    return this->action;
}

int robot::maxValue(State s, int alpha, int beta, int depth){ // the robot(max-er)
//    if(s.next.empty()){
//        return utility_endgame(s);
//    }
    if(s.next.empty() || depth >= depth_limit) {
        // no action can be made, terminate condition
        auto res = utility(s);
        return res;
    }
    int v = INT_MIN; // let v be negtive infinite
//    for(auto x : corners){
//        if(s.next.find(x) != s.next.end()){
//            if(depth == 0){
//                this->action = x;
//            }
//            return INT_MAX;
//        }
//    }
    for(auto iter = s.next.begin(); iter != s.next.end(); ++iter){
        // get the best utility we can got in this level
        auto state = get_next_state(s, *iter, BLACK);
        auto x = minValue(state, alpha, beta, depth + 1);
        if(v < x){
            v = x;
            if(depth == 0){ // add this in order to get the action for the max utility we got so far
//                int u = utility(state);
//                std::string str = std::to_string(u);
//                str += " there are" + std::to_string(s.next.size()) + "possiblities";
//                QMessageBox::about(othello::myWidget, "me", QString::fromStdString(str));
                this->action = *iter;
            }
        }
        if(v >= beta){
            return v;
        }
        alpha = std::max(alpha, v);
    }
    return v;
}

int robot::minValue(State s, int alpha, int beta, int depth){ // the player(min-er)
//    if(s.next.empty()){
//        return utility_endgame(s);
//    }
    if(s.next.empty() || depth >= depth_limit) {
        // no action can be made, terminate condition
        auto res = utility(s);
        return res;
    }
    int v = INT_MAX; //let v be positive infinite
    for(auto iter = s.next.begin(); iter != s.next.end(); ++iter){
        auto state = get_next_state(s, *iter, WHITE);
        v = std::min(v, maxValue(state, alpha, beta, depth + 1));
        if( v <= alpha){
            return v;
        }
        beta = std::min(beta, v);
    }
    return v;
}

State robot::get_next_state(State current_state, std::pair<int,int> action, int turn){
    assert(current_state.next.find(action) != current_state.next.end());
    assert(current_state.empty_set.find(action) != current_state.empty_set.end());
    // update the empty set
    current_state.empty_set.erase(action);

    // update the board
    int x = action.first;
    int y = action.second;
    current_state.board[x][y]->pieceColor = turn;

    for(auto dir : othello::dirs){
        // for all the directions
        int k = 1;
        int x_new = x + k * dir.first;
        int y_new = y + k * dir.second;
        while(x_new >= 0 && x_new < SIZE && y_new >= 0 && y_new < SIZE && current_state.board[x_new][y_new]->pieceColor == 1 - turn){
            // travese this direction
            ++k;
            x_new = x + k * dir.first;
            y_new = y + k * dir.second;
        }
        if(x_new >= 0 && x_new < SIZE && y_new >= 0 && y_new < SIZE && current_state.board[x_new][y_new]->pieceColor == turn){
            // the last while loop terminate because we meet the same pieceColor, we can update the board now
            for(int i = 1; i < k; ++i){
                x_new = x + i * dir.first;
                y_new = y + i * dir.second;
                current_state.board[x_new][y_new]->pieceColor = turn;
            }
        }
    }
    // change the next set for the next player
    // now the turn should be 1 - turn
    current_state.next.clear();
    for(auto iter = current_state.empty_set.begin(); iter!= current_state.empty_set.end(); ++iter){
        for(auto dir : othello::dirs){
            // traverse all the direction
            int x = iter->first + dir.first;
            int y = iter->second + dir.second;
            // first check if there is a differenct pieceColor nearby
            if(x >= 0 && x < SIZE && y >= 0 && y < SIZE && current_state.board[x][y]->pieceColor == turn){
                // if so, travese via this direction
                int k = 2;
                bool found = false; // flag if we can find the same pieceColor in the direction before meeting empty slot
                int x_new = iter->first + k * dir.first;
                int y_new = iter->second + k * dir.second;
                // travese via this direction to see if we can find the same before ending the loop
                while(x_new >= 0 && x_new < SIZE && y_new >= 0 && y_new < SIZE){
                    if(current_state.board[x_new][y_new]->pieceColor == 1 - turn){
                        // now we found the same peiceColor, time to break this loop
                        found = true;
                        break;
                    }
                    if(current_state.board[x_new][y_new]->pieceColor == EMPTY) {
                        found = false;
                        break;
                    }
                    ++k;
                    x_new = iter->first + k * dir.first;
                    y_new = iter->second + k * dir.second;
                }
                if(found){
                    // update the next set
                    current_state.next.insert(std::make_pair(iter->first,iter->second));
                }
            }
        }
    }
    return current_state;
}

int robot::utility(State s){

    int u = 0; // utility

    for(auto i = 0; i < SIZE; ++i){
        for(auto j = 0; j < SIZE; ++j){
            if(s.board[i][j]->pieceColor == BLACK){
                u += weights[i][j];
            }
            else if(s.board[i][j]->pieceColor == WHITE){
                u -= weights[i][j];
            }
        }
    }
    return u;
}
int robot::get_mobility(State current_state, int turn){

    int count = 0;

    for(auto iter = current_state.empty_set.begin(); iter!= current_state.empty_set.end(); ++iter){
        for(auto dir : othello::dirs){
            // traverse all the direction
            int x = iter->first + dir.first;
            int y = iter->second + dir.second;
            // first check if there is a differenct pieceColor nearby
            if(x >= 0 && x < SIZE && y >= 0 && y < SIZE && current_state.board[x][y]->pieceColor == 1 - turn){
                // if so, travese via this direction
                int k = 2;
                bool found = false; // flag if we can find the same pieceColor in the direction before meeting empty slot
                int x_new = iter->first + k * dir.first;
                int y_new = iter->second + k * dir.second;
                // travese via this direction to see if we can find the same before ending the loop
                while(x_new >= 0 && x_new < SIZE && y_new >= 0 && y_new < SIZE){
                    if(current_state.board[x_new][y_new]->pieceColor == turn){
                        // now we found the same peiceColor, time to break this loop
                        found = true;
                        break;
                    }
                    if(current_state.board[x_new][y_new]->pieceColor == EMPTY) {
                        found = false;
                        break;
                    }
                    ++k;
                    x_new = iter->first + k * dir.first;
                    y_new = iter->second + k * dir.second;
                }
                if(found){
                    // update the next set
                    ++count;
                }
            }
        }
    }
    return count;
}

double robot::heuristic(State s){
    int num_black = 0;
    int num_white = 0;
    for(auto i = 0; i < SIZE; ++i){
        for(auto j = 0; j < SIZE; ++j){
            if(s.board[i][j]->pieceColor == BLACK){
                num_black++;
            }
            else if(s.board[i][j]->pieceColor == WHITE){
                num_white++;
            }
        }
    }
    double cp_heuristic = 100 * (double)(num_black - num_white) / (double)(num_black + num_white);
    num_black = 0;
    num_white = 0;

    for (auto x : corners){
        if(s.board[x.first][x.second]->pieceColor == BLACK){
            num_black++;
        }
        else if(s.board[x.first][x.second]->pieceColor == WHITE){
            num_white++;
        }
    }
    double cor_heuristic = 100 * (double)(num_black - num_white) / (double)(num_black + num_white);
    return  cp_heuristic + cor_heuristic;
}
int robot::utility_endgame(State s){
    int num_black = 0;
    int num_white = 0;
    for(auto i = 0; i < SIZE; ++i){
        for(auto j = 0; j < SIZE; ++j){
            if(s.board[i][j]->pieceColor == BLACK){
                num_black++;
            }
            else if(s.board[i][j]->pieceColor == WHITE){
                num_white++;
            }
        }
    }
    return num_black - num_white;
}

robot::~robot(){
    // deconstructor
}

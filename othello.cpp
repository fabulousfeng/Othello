#include "othello.h"
#include <cassert>
extern bool start;
extern std::vector<std::vector<int>> weights;
int othello::turn = WHITE; // white go first
bool othello::running = false;

// the main board (SIZE*SIZE)
QWidget* othello::myWidget = NULL;

int othello::mode = ONEPLAYER;
int othello::difficulty = EASY;

auto othello::tile = std::vector<std::vector<Tile*>>(SIZE, std::vector<Tile*>(SIZE, NULL));

std::set<std::pair<int,int>> othello::empty_set;

std::set<std::pair<int,int>> othello::next;

QLabel* othello::label = NULL;
QLabel* othello::score1 = NULL;
QLabel* othello::score2 = NULL;
QLabel* othello::player1 = NULL;
QLabel* othello::player2 = NULL;
QLabel* othello::name1 = NULL;
QLabel* othello::name2 = NULL;

const std::vector<std::pair<int,int>> othello::dirs = {
        {-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}
};

othello::othello(QWidget *myWidget){

    othello::myWidget = myWidget;

    Border *border[4]={ NULL };
    //borderDisplay
    {
    border[0]->outline(myWidget,330,105,0);
    border[1]->outline(myWidget,330,637,0);
    border[2]->outline(myWidget,330,125,1);
    border[3]->outline(myWidget,862,125,1);
    }
   othello::running = false;
   othello::init();
}
void othello::init(){

    int i,j,k = 0,hor,ver;
    //Create 64 tiles 8*8
    ver = 125;
    for(i = 0;i < SIZE;i++)
    {
        hor = 350;
        for(j = 0;j < SIZE;j++)
        {
            othello::tile[i][j] = new Tile(othello::myWidget);
            othello::tile[i][j]->tileColor = (i + j) % 2; // different colors
            othello::tile[i][j]->pieceColor = EMPTY; // no pieces in this tile
            othello::tile[i][j]->row = i;
            othello::tile[i][j]->col = j;
            othello::empty_set.insert(std::make_pair(i,j));
            othello::tile[i][j]->tileNum = k++;// k = 4*i+j
            othello::tile[i][j]->tileDisplay();
            othello::tile[i][j]->setGeometry(hor, ver, 64, 64);
            hor += 64;
        }
        ver += 64;
    }

    // intialize the game
    othello::tile[3][3]->pieceColor = BLACK; // 0 is black
    othello::tile[3][3]->display(BLACK);
    othello::empty_set.erase(std::make_pair(3,3));

    othello::tile[4][4]->pieceColor = BLACK;
    othello::tile[4][4]->display(BLACK);
    othello::empty_set.erase(std::make_pair(4,4));

    othello::tile[3][4]->pieceColor = WHITE; // 1 is white
    othello::tile[3][4]->display(WHITE);
    othello::empty_set.erase(std::make_pair(3,4));

    othello::tile[4][3]->pieceColor = WHITE;
    othello::tile[4][3]->display(WHITE);
    othello::empty_set.erase(std::make_pair(4,3));


    othello::update_next(); // update the list for all the possible next steps

    // user infomation

    if(othello::mode == ONEPLAYER){

        othello::label = new QLabel("Your(White) turn",othello::myWidget);

        othello::player1 = new QLabel(othello::myWidget);
        othello::name1 = new QLabel("Feng (Black)", othello::myWidget);
        othello::score1 = new QLabel("Score: 2", othello::myWidget);

        othello::player2 = new QLabel(othello::myWidget);
        othello::name2 = new QLabel("You (White)", othello::myWidget);
        othello::score2 = new QLabel("Score: 2", othello::myWidget);
    }
    else{

        othello::label = new QLabel("Player 1's(White) turn",othello::myWidget);

        othello::player1 = new QLabel(othello::myWidget);
        othello::name1 = new QLabel("Player 2 (Black)", othello::myWidget);
        othello::score1 = new QLabel("Score: 2", othello::myWidget);

        othello::player2 = new QLabel(othello::myWidget);
        othello::name2 = new QLabel("Player 1 (White)", othello::myWidget);
        othello::score2 = new QLabel("Score: 2", othello::myWidget);
    }

    othello::label->setGeometry(500,30,300,50);
    othello::label->setStyleSheet("QLabel {color:red; font-size: 25px}");

    othello::name1->setGeometry(125,460,120,20);
    othello::score1->setGeometry(120,485,180,40);
    othello::player1->setGeometry(100,350,100,100);
    othello::player1->setPixmap(QPixmap(":/Images/profile.png"));

    othello::name2->setGeometry(125,210,120,20);
    othello::score2->setGeometry(120,235,180,40);
    othello::player2->setGeometry(100,100,100,100);
    othello::player2->setPixmap(QPixmap(":/Images/profile.png"));

    othello::show_next(true);
}
void othello::check_game(){
    int score1_ = 0;  // Feng or player 2 (black)
    int score2_ = 0;  // You or player 1 (white)
    for(int i = 0; i < SIZE; ++i){
        for(int j = 0; j < SIZE; ++j){
            if(othello::tile[i][j]->pieceColor == WHITE){
                ++score2_;
            }
            else if(othello::tile[i][j]->pieceColor == BLACK){
                ++score1_;
            }
        }
    }
    if(othello::mode == ONEPLAYER){
        if(score1_ > score2_){
            QMessageBox::about(othello::myWidget,"Result","Sorry, you(White) lost!");
        }
        else if(score1_ < score2_){
            QMessageBox::about(othello::myWidget,"Result","Congrats, you(White) win!");
        }
        else{
            QMessageBox::about(othello::myWidget,"Result","It is a tie!");
        }
    }
    else{ // two players
        if(score1_ > score2_){
            QMessageBox::about(othello::myWidget,"Result","Player 2(Black) wins!");
        }
        else if(score1_ < score2_){
            QMessageBox::about(othello::myWidget,"Result","Player 1(White) wins!");
        }
        else{
            QMessageBox::about(othello::myWidget,"Result","It is a tie!");
        }

    }
}
void othello::show_turn(){
    if(othello::mode == TWOPLAYER){
        if(othello::turn == WHITE){
            othello::label->setText("Player 1's(White) turn");
        }
        else{
            othello::label->setText("Player 2's(Black) turn");
        }
    }
    else if(othello::mode == ONEPLAYER){
        if(othello::turn == WHITE){
            othello::label->setText("Your(White) turn");
        }
        else{
            othello::label->setText("Feng's(Black) turn");
        }
    }
}

void othello::game_update(int x, int y){
    if(!start) {
        QMessageBox::information(othello::myWidget,"Tips", "Please click Play Now to start!");
        return;
    }
    if(othello::mode == ONEPLAYER && othello::turn != WHITE) return;// can not make a step if it is not your turn
    if(!othello::tile[x][y]) return; // for safe, error checking
    if(othello::tile[x][y]->pieceColor != EMPTY) return;  // must put in an empty position

    if(othello::next.find(std::make_pair(x,y)) == othello::next.end()) return; // must put the pieces in the next available position

    if(!othello::running) {
        othello::running = true;
    }
    othello::show_next(false); // hide all possible moves in the last step

    othello::update_board(x, y, false); // update the borad of the game

    othello::turn = 1 - othello::turn; // switch to the next player
    othello::update_next(); // now the next list should have all next available positions for the next player

    othello::show_turn();

    if(othello::next.empty()){
        othello::running = false; // game is ended!
        start = false;
        // judge who wins the game
        othello::check_game();
        return;
    }

    othello::show_next(true);

    if(othello::mode == ONEPLAYER && othello::difficulty == EASY){
        // single player, easy mode
        othello::robot_easy();
    }
    else if(othello::mode == ONEPLAYER && othello::difficulty == MEDIUM){
        // single player, medium mode
        othello::computer(DEPTH_MEDIUM);
    }
    else if(othello::mode == ONEPLAYER && othello::difficulty == HARD){
        // single player, hard mode
        othello::computer(DEPTH_HARD);
    }
}

void othello::update_next(){
    // clear the set becasue we changed the player
    othello::next.clear();
    // the next available steps must be in the empty set
    for(auto iter = othello::empty_set.begin(); iter!= othello::empty_set.end(); ++iter){
        for(auto dir : dirs){
            // traverse all the direction
            int x = iter->first + dir.first;
            int y = iter->second + dir.second;
            // first check if there is a differenct pieceColor nearby
            if(x >= 0 && x < SIZE && y >= 0 && y < SIZE && othello::tile[x][y]->pieceColor == 1 - othello::turn){
                // if so, travese via this direction
                int k = 2;
                bool found = false; // flag if we can find the same pieceColor in the direction before meeting empty slot
                int x_new = iter->first + k * dir.first;
                int y_new = iter->second + k * dir.second;
                // travese via this direction to see if we can find the same before ending the loop
                while(x_new >= 0 && x_new < SIZE && y_new >= 0 && y_new < SIZE){
                    if(othello::tile[x_new][y_new]->pieceColor == othello::turn){
                        // now we found the same peiceColor, time to break this loop
                        found = true;
                        break;
                    }
                    if(othello::tile[x_new][y_new]->pieceColor == EMPTY) {
                        found = false;
                        break;
                    }
                    ++k;
                    x_new = iter->first + k * dir.first;
                    y_new = iter->second + k * dir.second;
                }
                if(found){
                    // update the next set
                    othello::next.insert(std::make_pair(iter->first,iter->second));
                }
            }
        }
    }
}

void othello::update_board(int x, int y, bool fade){
    // pop out from the empty set
    othello::empty_set.erase(std::make_pair(x,y));
    // update the tile for which clicked by the player
    if(fade){
        othello::tile[x][y]->fadeIn(othello::turn, 500);
    }else{
        othello::tile[x][y]->display(othello::turn);
    }

    for(auto dir : dirs){
        // for all the directions
        int k = 1;
        int x_new = x + k * dir.first;
        int y_new = y + k * dir.second;
        while(x_new >= 0 && x_new < SIZE && y_new >= 0 && y_new < SIZE && othello::tile[x_new][y_new]->pieceColor == 1 - othello::turn){
            // travese this direction
            ++k;
            x_new = x + k * dir.first;
            y_new = y + k * dir.second;
        }
        if(x_new >= 0 && x_new < SIZE && y_new >= 0 && y_new < SIZE && othello::tile[x_new][y_new]->pieceColor == othello::turn){
            // the last while loop terminate because we meet the same pieceColor, we can update the board now
            for(int i = 1; i < k; ++i){
                x_new = x + i * dir.first;
                y_new = y + i * dir.second;
                if(fade){
                    othello::tile[x_new][y_new]->fadeIn(othello::turn, 1800);
                }else{
                    othello::tile[x_new][y_new]->display(othello::turn);
                }
            }
        }
    }
    othello::score_update();
}
void othello::show_next(bool show){
    for(auto iter = othello::next.begin(); iter != othello::next.end(); ++iter){
        int x = iter->first;
        int y = iter->second;
        if(show){
            othello::tile[x][y]->setStyleSheet("QLabel {background-color: rgb(150, 150, 150);}:hover{background-color: rgb(170,85,127);}");
        }
        else{
            othello::tile[x][y]->tileDisplay();
        }
    }
}
void othello::score_update(){
    int score1_ = 0;  // Feng (black)
    int score2_ = 0;  // You  (white)
    for(int i = 0; i < SIZE; ++i){
        for(int j = 0; j < SIZE; ++j){
            if(othello::tile[i][j]->pieceColor == WHITE){
                ++score2_;
            }
            else if(othello::tile[i][j]->pieceColor == BLACK){
                ++score1_;
            }
        }
    }
    std::string s1 = "Score: " + std::to_string(score1_);
    std::string s2 = "Score: " + std::to_string(score2_);

    othello::score1->setText(QString::fromStdString(s1));
    othello::score2->setText(QString::fromStdString(s2));

}
void othello::robot_easy(){
    // robot use the black color, so this turn must be BLACK
    // the easy robot, which use a greedy stratage to make the next move

    assert(othello::turn == BLACK); // this function only works for robot which uses BLACK
    assert(othello::mode == ONEPLAYER); // this function only works for one player mode

    othello::show_next(false); // hide all possible moves in the last step

    int utility_max = INT_MIN; // only focus on the current profit, a greedy stratage
    int x_max = 0;
    int y_max = 0;
    for(auto iter = othello::next.begin(); iter != othello::next.end(); ++iter){
        auto current_utility = utility_easy(iter->first, iter->second);
        if(current_utility > utility_max){
            utility_max = current_utility;
            x_max = iter->first;
            y_max = iter->second;
        }
    }

    // update the game borad by the chosen action
    othello::update_board(x_max, y_max, true);

    othello::turn = 1 - othello::turn; // switch back to player
    othello::update_next(); // now the next list should have all next available positions for the next player
    othello::show_turn();
    if(othello::next.empty()){
        othello::running = false; // game is ended!
        start = false;
        // judge who wins the game
        othello::check_game();
        return;
    }

    othello::show_next(true);

}
int othello::utility_easy(int x, int y){
    // use a greedy stratage to make the next step
    // which means the robot always select the step that can reverse to get the largest rewards by the weights
    // Of course it does not consider future effects so we consider it is a easy mode
    // it means our opponents may have a big reverse in the future game

   int utility = weights[x][y]; // the immediate reward

    for(auto dir : dirs){
        // for all the directions
        int temp = 0;
        int k = 1;
        int x_new = x + k * dir.first;
        int y_new = y + k * dir.second;
        while(x_new >= 0 && x_new < SIZE && y_new >= 0 && y_new < SIZE && othello::tile[x_new][y_new]->pieceColor == 1 - othello::turn){
            // travese this direction
            temp += weights[x_new][y_new];// the weight of this new position we may get
            ++k;
            x_new = x + k * dir.first;
            y_new = y + k * dir.second;

        }
        if(x_new >= 0 && x_new < SIZE && y_new >= 0 && y_new < SIZE && othello::tile[x_new][y_new]->pieceColor == othello::turn){
            // the last while loop terminate because we meet the same pieceColor, we can update the board now
            utility += temp;
        }
    }
    return utility;
}
void othello::computer(int depth){

    othello::show_next(false); // hide all possible moves in the last step

    State current_state;
    // do a deep copy
    current_state.board = std::vector<std::vector<Tile*>>(SIZE, std::vector<Tile*>(SIZE, NULL));
    for(int i = 0; i < SIZE; ++i){
        for(int j = 0; j < SIZE; ++j){
            current_state.board[i][j] = new Tile();

            current_state.board[i][j]->tileColor = othello::tile[i][j]->tileColor;
            current_state.board[i][j]->pieceColor = othello::tile[i][j]->pieceColor;
            current_state.board[i][j]->row = i;
            current_state.board[i][j]->col = j;
            current_state.board[i][j]->tileNum = othello::tile[i][j]->tileNum;
        }
    }
    current_state.next = othello::next;

    current_state.empty_set = othello::empty_set;

    // create an instance of our robot(hard)
    robot comp(current_state, depth);

    // using alpha_beta_prunning to search for an action
    std::pair<int, int> action = comp.alpha_beta_search();

    // do an update in the game board

    int x_max = action.first;
    int y_max = action.second;

    othello::update_board(x_max, y_max, true);

    othello::turn = 1 - othello::turn; // switch back to player
    othello::update_next(); // now the next list should have all next available positions for the next player
    othello::show_turn();
    if(othello::next.empty()){
        othello::running = false; // game is ended!
        start = false;
        // judge who wins the game
        othello::check_game();
        return;
    }
    othello::show_next(true);

    //free memory
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; ++j){
                delete current_state.board[i][j];
        }
    }
    int u = othello::utility();
//    std::string str = "current: ";
//    str += std::to_string(u);
//    QMessageBox::about(othello::myWidget, "me", QString::fromStdString(str));
}
int othello::utility(){
        int u = 0; // utility
        for(auto i = 0; i < SIZE; ++i){
            for(auto j = 0; j < SIZE; ++j){
                if(othello::tile[i][j]->pieceColor == BLACK){
                    u += weights[i][j];
                }
                else if(othello::tile[i][j]->pieceColor == WHITE){
                    u -= weights[i][j];
                }
            }
        }
        return u;
}

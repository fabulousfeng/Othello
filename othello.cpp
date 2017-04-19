#include "othello.h"
extern bool start;
int othello::turn = WHITE; // white go first
bool othello::running = false;
// the main board (SIZE*SIZE)
QWidget* othello::myWidget = NULL;
int othello::mode = ONEPLAYER;
auto othello::tile = std::vector<std::vector<Tile*>>(SIZE, std::vector<Tile*>(SIZE, NULL));

std::set<std::pair<int,int>> othello::empty_set;

std::set<std::pair<int,int>> othello::next;

QLabel* othello::score1 = NULL;
QLabel* othello::score2 = NULL;

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


    othello::update_next(); // update the list for all the possible next stepss
    QLabel *player1,*player2;
    QLabel *name1,*name2;
    // user infomation
    if(othello::mode == ONEPLAYER){
        player1 = new QLabel(othello::myWidget);
        name1 = new QLabel("Feng", othello::myWidget);
        othello::score1 = new QLabel("Feng's Score: 2", othello::myWidget);

        player2 = new QLabel(othello::myWidget);
        name2 = new QLabel("You", othello::myWidget);
        othello::score2 = new QLabel("Your Score: 2", othello::myWidget);
    }
    else{
        player1 = new QLabel(othello::myWidget);
        name1 = new QLabel("Player 1", othello::myWidget);
        othello::score1 = new QLabel("Player 1's Score: 2", othello::myWidget);

        player2 = new QLabel(othello::myWidget);
        name2 = new QLabel("Player 2", othello::myWidget);
        score2 = new QLabel("Player 2's Score: 2", othello::myWidget);
    }
    name1->setGeometry(125,460,80,20);
    othello::score1->setGeometry(120,485,180,40);
    player1->setGeometry(100,350,100,100);
    player1->setPixmap(QPixmap(":/Images/profile.png"));

    name2->setGeometry(125,210,80,20);
    othello::score2->setGeometry(120,235,180,40);
    player2->setGeometry(100,100,100,100);
    player2->setPixmap(QPixmap(":/Images/profile.png"));

    othello::show_next(true);
}

void othello::game_update(int x, int y){
    if(!start) {
        QMessageBox::information(othello::myWidget,"Tips", "Please click Play Now to start!");
        return;
    }
    if(!othello::tile[x][y]) return;
    if(othello::tile[x][y]->pieceColor != EMPTY) return;  // must put in an empty position

    if(othello::next.find(std::make_pair(x,y)) == othello::next.end()) return; // must put the pieces in the next available position

    othello::running = true;

    othello::show_next(false);
    othello::update_board(x, y); // update the borad of the game

    othello::turn = 1 - othello::turn; // switch to the next player
    othello::update_next(); // now the next list should have all next available positions for the next player
    if(othello::next.empty()){
        QMessageBox::about(othello::myWidget,"Result","You lost!");
    }
    othello::show_next(true);
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

void othello::update_board(int x, int y){
    // pop out from the empty set
    othello::empty_set.erase(std::make_pair(x,y));
    // update the tile for which clicked by the player
    othello::tile[x][y]->display(othello::turn);

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
                othello::tile[x_new][y_new]->display(othello::turn);
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
    std::string s1,s2;
    if(othello::mode == ONEPLAYER){
        std::string s1 = "Feng's Score: " + std::to_string(score1_);
        std::string s2 = "Your Score: " + std::to_string(score2_);
    }
    else{
        std::string s1 = "Player 1's Score: " + std::to_string(score1_);
        std::string s2 = "Player 2's Score: " + std::to_string(score2_);
    }

    othello::score1->setText(QString::fromStdString(s1));
    othello::score2->setText(QString::fromStdString(s2));

}

#include "othello.h"

int othello::turn = WHITE; // white go first

// the main board (SIZE*SIZE)
auto othello::tile = std::vector<std::vector<Tile*>>(SIZE, std::vector<Tile*>(SIZE, NULL));
std::set<std::pair<int,int>> othello::empty_set;
std::set<std::pair<int,int>> othello::next;
const std::vector<std::pair<int,int>> othello::dirs = {
        {-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}
};

othello::othello(QWidget *myWidget){

    this->myWidget = myWidget;
    int i,j,k = 0,hor,ver;
    //Create 64 tiles 8*8
    ver = 125;
    for(i = 0;i < SIZE;i++)
    {
        hor = 350;
        for(j = 0;j < SIZE;j++)
        {
            othello::tile[i][j] = new Tile(myWidget);
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


    update_next(); // update the list for all the possible next stepss

    // user infomation
    QLabel *player2 = new QLabel(myWidget);
    QLabel *name2 = new QLabel("Player 2", myWidget);
    QLabel *time2 = new QLabel("00:00:00", myWidget);

    QLabel *player1 = new QLabel(myWidget);
    QLabel *name1 = new QLabel("Player 1", myWidget);
    QLabel *time1 = new QLabel("00:00:00", myWidget);

    QLabel *moves = new QLabel(myWidget);

    name1->setGeometry(125,610,80,20);
    time1->setGeometry(120,635,80,20);
    player1->setGeometry(100,500,100,100);
    player1->setPixmap(QPixmap(":/Images/profile.png"));

    name2->setGeometry(125,210,80,20);
    time2->setGeometry(120,235,80,20);
    player2->setGeometry(100,100,100,100);
    player2->setPixmap(QPixmap(":/Images/feng2.png"));

    moves->setGeometry(1000,105,250,550);
    moves->setStyleSheet("QLabel {background-color: yellow;}");


}
void othello::game_update(int x, int y){
    if(othello::tile[x][y]->pieceColor != EMPTY) return;  // must put in an empty position

    if(othello::next.find(std::make_pair(x,y)) == othello::next.end()) return; // must put the pieces in the next available position

    othello::empty_set.erase(std::make_pair(x,y));

    update_board(x, y); // update the borad of the game

    othello::turn = 1 - othello::turn; // switch to the next player

    update_next(); // now the next list should have all next available positions for the next player
}

void othello::update_next(){
    // clear the set becasue we changed the player
    othello::next.clear();
    // the next available steps must be in the empty set
    for(auto iter = empty_set.begin(); iter!= empty_set.end(); ++iter){
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
        if(x_new >= 0 && x_new < SIZE && y_new >= 0 && y_new < SIZE && (othello::tile[x_new][y_new]->pieceColor == othello::turn)){
            // the last while loop terminate because we meet the same pieceColor, we can update the board now
            for(int i = 1; i < k; ++i){
                x_new = x + i * dir.first;
                y_new = y + i * dir.second;
                othello::tile[x_new][y_new]->display(othello::turn);
            }
        }
    }
}

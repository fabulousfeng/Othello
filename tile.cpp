#include "tile.h"
#include "othello.h"
// global variables


void Tile::mousePressEvent(QMouseEvent *event)
{
    othello::game_update(row, col);
}

void Tile::display(int pieceColor)
{
    this->pieceColor = pieceColor;

    if(this->pieceColor == WHITE)
    {
        this->setPixmap(QPixmap(":/Images/white.png"));
    }

    else if(this->pieceColor == BLACK)
    {
        this->setPixmap(QPixmap(":/Images/black.png"));
    }
    else{ // EMPTY
        this->clear();
    }
}
void Tile::tileDisplay()
{
    if(this->tileColor)
        this->setStyleSheet("QLabel {background-color: rgb(120, 120, 90);}:hover{background-color: rgb(170,85,127);}");
    else
        this->setStyleSheet("QLabel {background-color: rgb(211, 211, 158);}:hover{background-color: rgb(170,85,127);}");

}

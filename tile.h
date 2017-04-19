#ifndef TILE_H
#define TILE_H

#include <QLabel>
#include <QMessageBox>
#include <QDebug>

#include <set>
#include <vector>

#define WHITE 1
#define BLACK 0
#define EMPTY -1

class Tile: public QLabel
{
public:
    // members
    int pieceColor; // 1 means white, 0 means black, -1 means empty
    int row;        // the row this tile is in
    int col;        // the colomn this tile is in
    int tileNum;    // 4*row + col
    int tileColor;
    //Constructors
    Tile(QWidget* pParent=0, Qt::WindowFlags f=0) : QLabel(pParent, f) {};
    Tile(const QString& text, QWidget* pParent = 0, Qt::WindowFlags f = 0) : QLabel(text, pParent, f){};

    //Methods
    void mousePressEvent(QMouseEvent *event);
    void display(int pieceColor);
    void display();
    void tileDisplay();
};

#endif // TILE_H

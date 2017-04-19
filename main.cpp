#include <QApplication>
#include "mainwindow.h"
#include "tile.h"
#include "othello.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QWidget *myWidget = new QWidget();
    myWidget->setGeometry(0,0,1370,700);

    othello oth(myWidget);

    myWidget->show();

    return a.exec();
}


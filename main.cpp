#include <QApplication>
#include "othello_widget.h"
#include "tile.h"
#include "othello.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    auto myWidget = new Othello_Widget();
    myWidget->setGeometry(0,0,1370,700);

    othello oth(myWidget);

    myWidget->show();

    return a.exec();
}


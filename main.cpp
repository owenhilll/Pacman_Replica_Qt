#include "gameboard.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameBoard w;
    w.display();
    w.show();

    return a.exec();
}

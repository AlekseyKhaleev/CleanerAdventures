#include "gamewidget.h"
#include <QApplication>
#include "Maze.h"
#include "Robot.h"


using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameWidget w;
    w.showFullScreen();
    return a.exec();
}

#include <Maze.h>
#include <QApplication>
#include <Robot.h>
//#include "mainwindow.h"
#include "GameWidget.h"

using namespace std;

int main(int argc, char* argv[]){
    QApplication app(argc, argv);

//    MainWindow main_w;
//    main_w.showFullScreen();
    GameWidget game;
    game.showFullScreen();
    return app.exec();
}

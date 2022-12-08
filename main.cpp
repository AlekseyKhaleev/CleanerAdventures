#include <Map.h>
#include <QApplication>
#include <Robot.h>

using namespace std;

int main(int argc, char* argv[]){
    QApplication app(argc, argv);

    Robot game;
//    Map map;
//    map.show();
    game.show();
    return app.exec();
}

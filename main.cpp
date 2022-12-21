#include <QApplication>
#include <QPainter>

#include "GameWidget.h"


using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GameWidget w;    
    w.showFullScreen();

    return a.exec();
}

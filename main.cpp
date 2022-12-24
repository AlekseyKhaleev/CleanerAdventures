#include <QApplication>
#include <QPainter>
#include "MainWidget.h"


using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWidget mainWindow;
    mainWindow.showFullScreen();


    return QApplication::exec();

}

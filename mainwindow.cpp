#include "mainwindow.h"
#include "Robot.h"
#include <QVBoxLayout>
#include <QStatusBar>
#include <QActionGroup>
#include <QMenu>
#include <QMenuBar>
#include <QContextMenuEvent>
#include "energyWidget.h"
#include <QFontDatabase>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
{
    QWidget *widget = new QWidget;
        setCentralWidget(widget);
        widget->setStyleSheet("QWidget {background-color: black; color: white;}");

        QWidget *topFiller = new QWidget;
        topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        Robot *game = new Robot;
        game->setFixedSize(game->size());
        game->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        game->setFocusPolicy(Qt::StrongFocus);
        game->setStyleSheet("QWidget {background-color: white; color: black;}");


        QLabel *energy = new EnergyWidget(game);
        energy->setFixedSize(energy->size());
        energy->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        energy->setFixedSize(700,85);
//        energy->setAlignment(Qt::AlignLeft);
//        energy->setStyleSheet("QWidget {background-color: white; color: black;}");

        QHBoxLayout *displayStatus = new QHBoxLayout;
        displayStatus->setContentsMargins(2,2,2,2);
        displayStatus->addWidget(energy,1,Qt::AlignLeft);

//        infoLabel = new QLabel(tr("<i>Choose a menu option, or right-click to "
//                                  "invoke a context menu</i>"));
//        infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
//        infoLabel->setAlignment(Qt::AlignCenter);

        QWidget *bottomFiller = new QWidget;
        bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        QVBoxLayout *layout = new QVBoxLayout;
        layout->setContentsMargins(5, 5, 5, 5);

        layout->addWidget(topFiller);
        layout->addLayout(displayStatus);
        layout->addWidget(game);
        layout->addWidget(bottomFiller);
        widget->setLayout(layout);
        createActions();
        createMenus();

        QString message = tr("A context menu is available by right-clicking");
        statusBar()->showMessage(message);

        setWindowTitle(tr("Menus"));
        setMinimumSize(minimumSizeHint());

//        setMinimumHeight(game->height());



}

void MainWindow::createActions()
{
    newAct = new QAction(tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, &QAction::triggered, this, &MainWindow::newFile);

    openAct = new QAction(tr("&Open"), this);
    openAct->setShortcuts(QKeySequence::New);
    openAct->setStatusTip(tr("Open a new file"));
    connect(openAct, &QAction::triggered, this, &MainWindow::open);

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::New);
    saveAct->setStatusTip(tr("Save the current file"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::save);

    printAct = new QAction(tr("&Print"), this);
    printAct->setShortcuts(QKeySequence::New);
    printAct->setStatusTip(tr("Print highscores"));
    connect(printAct, &QAction::triggered, this, &MainWindow::print);

    exitAct = new QAction(tr("&Exit"), this);
    exitAct->setShortcuts(QKeySequence::New);
    exitAct->setStatusTip(tr("Exit app"));
    connect(exitAct, &QAction::triggered, this, &MainWindow::exit);

    undoAct = new QAction(tr("&Undo"), this);
    undoAct->setShortcuts(QKeySequence::New);
    undoAct->setStatusTip(tr("Step undo"));
    connect(undoAct, &QAction::triggered, this, &MainWindow::undo);

    aboutAct = new QAction(tr("&Help"), this);
    aboutAct->setShortcuts(QKeySequence::New);
    aboutAct->setStatusTip(tr("Show helpscreen"));
    connect(aboutAct, &QAction::triggered, this, &MainWindow::about);

    alignmentGroup = new QActionGroup(this);

}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(undoAct);

    editMenu->addSeparator();

    editMenu->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    formatMenu = editMenu->addMenu(tr("&Format"));
    formatMenu->addSeparator()->setText(tr("Alignment"));
    formatMenu->addSeparator();

}

#ifndef QT_NO_CONTEXTMENU
void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
//    menu.addAction(cutAct);
//    menu.addAction(copyAct);
//    menu.addAction(pasteAct);
    menu.exec(event->globalPos());
}
#endif // QT_NO_CONTEXTMENU

void MainWindow::newFile()
{

}

void MainWindow::open()
{

}

void MainWindow::save()
{

}

void MainWindow::print()
{

}

void MainWindow::undo()
{

}

void MainWindow::about()
{

}

void MainWindow::exit()
{

}


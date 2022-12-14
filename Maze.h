#pragma once

#include <QWidget>
#include <QVector>
#include <QPoint>
#include <QMap>
#include <QObject>
#include <QGuiApplication>
#include <QScreen>



class Maze: public QWidget
{
    Q_OBJECT
public:
    Maze();


protected:
    static const int DOT_WIDTH    = 34;
    static const int DOT_HEIGHT   = 34;
    int FIELD_WIDTH;  //= 47;
    int FIELD_HEIGHT; //= 21;

    QSet<QPoint> m_walls;
    QSet<QPoint> m_cells;

    QPoint getRandDot();

    void initMaze();
    void gameOver();
    void drawMaze();
    QVector<QPoint> getMazeNeighbours(QPoint current, QSet<QPoint> cells);

private:
    void initFieldSize();
    void initDefaultMazeMap();
    void locateWalls();
};


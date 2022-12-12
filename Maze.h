#pragma once

#include <QWidget>
#include <QVector>
#include <QPoint>
#include <QMap>
#include <QObject>


class Maze: public QWidget
{
//    Q_OBJECT
public:
    Maze();
    static const int DOT_WIDTH    = 30;
    static const int DOT_HEIGHT   = 30;
    static const int FIELD_WIDTH  = 53;//45
    static const int FIELD_HEIGHT = 23;//21

protected:



    void paintEvent(QPaintEvent *event) override;
    QSet<QPoint> m_walls;
    QSet<QPoint> m_cells;

    QPoint getRandDot();

    void initMaze();
    void gameOver();
    void drawMaze();
    virtual QVector<QPoint> getNeighbours(QPoint current, QSet<QPoint> cells);



private:

    void locateWalls();


};


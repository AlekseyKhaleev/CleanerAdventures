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
    static const int DOT_WIDTH    = 35;
    static const int DOT_HEIGHT   = 35;
    static const int FIELD_WIDTH  = 45;
    static const int FIELD_HEIGHT = 21;

protected:



    void paintEvent(QPaintEvent *event) override;
    QSet<QPoint> m_walls;
    QSet<QPoint> m_cells;
    bool m_inGame;
    int m_steps;
    QPoint getRandDot();

    void initMaze();
    void gameOver();
    void drawMaze();

private:

    void locateWalls();
    QVector<QPoint> getNeighbours(QPoint current);

};


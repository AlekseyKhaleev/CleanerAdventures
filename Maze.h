#pragma once

#include <QWidget>
#include <QVector>
#include <QPoint>
#include <QMap>


class Maze: public QWidget
{
public:
    Maze();

protected:

    static const int DOT_WIDTH    = 30;
    static const int DOT_HEIGHT   = 30;
    static const int FIELD_WIDTH  = 25;
    static const int FIELD_HEIGHT = 25;

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


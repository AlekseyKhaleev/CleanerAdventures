#pragma once

#include <QWidget>
#include <QVector>
#include <QPoint>
#include <QMap>


class Map: public QWidget
{
public:
    Map();

protected:

    static const int DOT_WIDTH    = 20;
    static const int DOT_HEIGHT   = 20;
    static const int FIELD_WIDTH  = 35;
    static const int FIELD_HEIGHT = 35;

    void paintEvent(QPaintEvent *event) override;
    QSet<QPoint> m_walls;
    QSet<QPoint> m_cells;
    QPoint m_target{-1,-1};
    QPoint m_start;
    bool m_inGame;
    int m_steps;
    QPoint getRandDot();
    void gameOver();
    void drawMap();

private:

    static const int WALLS_COUNT = 40;
    static const int WALL_MAX_LEN = 6;

    QVector<QPoint> m_lines;

    void initGame();

    void locateStart();
    void locateWalls();
    void locateLines();
    QVector<QPoint> getNeighbours(QPoint current);

};


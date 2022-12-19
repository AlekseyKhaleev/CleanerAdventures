#pragma once

#include <QGuiApplication>
#include <QMap>
#include <QObject>
#include <QPoint>
#include <QVector>
#include <QScreen>
#include <QSet>
#include <QWidget>

inline uint qHash(const QPoint &key) { return (key.x() << 16) + key.y(); }

class Maze: public QWidget
{
    Q_OBJECT
public:
    Maze(QWidget *parent = nullptr);


protected:
    static const int DOT_WIDTH    = 34;
    static const int DOT_HEIGHT   = 34;
    int FIELD_WIDTH;  //= 47;
    int FIELD_HEIGHT; //= 21;

    QSet<QPoint> m_walls;
    QSet<QPoint> m_cells;

    QPoint getRandDot();

    void initMaze();
    static QVector<QPoint> getMazeNeighbours(QPoint current, const QSet<QPoint>& cells);

private:
    void initFieldSize();
    void initDefaultMazeMap();
    void locateWalls();
};


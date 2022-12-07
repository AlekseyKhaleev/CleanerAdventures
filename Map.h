#pragma once

#include <QWidget>
#include <QVector>
#include <QPoint>


class Map: public QWidget
{
public:
    Map();

protected:

    static const int DOT_WIDTH    = 20;
    static const int DOT_HEIGHT   = 20;
    static const int FIELD_WIDTH  = 20;
    static const int FIELD_HEIGHT = 20;

//    void timerEvent(QTimerEvent *event) override;
//    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

    QVector<QPoint> m_walls;
    QPoint m_target;
    bool m_inGame;
    QPoint getRandDot();
    void gameOver();
    void doDrawing();

private:

    static const int WALLS_COUNT = 40;
    static const int WALL_MAX_LEN = 6;

 //    static const int DELAY = 150;
 //    int m_timerId;


    QVector<QPoint> m_lines;


    //    enum Directions{
    //        left, right, up, down
    //    } m_dir;


    void initGame();

    QPoint locateTarget();
    void locateWalls();
    void locateLines();


//    void move();
//    void check_field();
//    void check_target();

};


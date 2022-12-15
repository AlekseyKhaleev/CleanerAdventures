#pragma once

#include <QImage>
#include <QMap>
#include <QObject>
#include <QPoint>
#include <QStack>
#include "Maze.h"
#include <iostream>
#include <memory>

class Robot : public Maze{
    Q_OBJECT

public:
    Robot();
    ~Robot();

signals:
    void energyChanged(int energy);
    void scoreChanged(int score);
    void levelChanged(int level);

private:
    static const int ANIMATION_DELAY = 300;

    enum Directions { left, right, up, down } m_robotDestination;

    enum Colors{
        white, green, yellow, red
    }m_curColor, m_tmpColor;

    struct State
    {
        QPoint POSITION;
        QVector<QPoint> BATTERIES;
        int SCORE;
        int ENERGY;
        int STEPS;
        Directions DESTINATION;
        Colors CURRENT_COLOR;
        Colors TEMPORARY_COLOR;

        State() = default;
        State(QPoint position,
              QVector<QPoint> batteries,
              int score,
              int energy,
              int steps,
              Directions destination,
              Colors current,
              Colors temp)
        {
            POSITION = position;
            BATTERIES = batteries;
            SCORE = score;
            ENERGY = energy;
            STEPS = steps;
            DESTINATION = destination;
            CURRENT_COLOR = current;
            TEMPORARY_COLOR = temp;
        }
    };

    QImage m_batteryImage{"../icons/battery"};
    QImage m_targetImage{"../icons/target"};
    QVector<QImage> m_white{
        QImage("../icons/VC_wt_lt"),
        QImage("../icons/VC_wt_rt"),
        QImage("../icons/VC_wt_up"),
        QImage("../icons/VC_wt_dn"),
    };
    QVector<QImage> m_green{
        QImage("../icons/VC_gr_lt"),
        QImage("../icons/VC_gr_rt"),
        QImage("../icons/VC_gr_up"),
        QImage("../icons/VC_gr_dn"),
    };
    QVector<QImage> m_yellow{
        QImage("../icons/VC_yw_lt"),
        QImage("../icons/VC_yw_rt"),
        QImage("../icons/VC_yw_up"),
        QImage("../icons/VC_yw_dn"),
    };
    QVector<QImage> m_red{
        QImage("../icons/VC_rd_lt"),
        QImage("../icons/VC_rd_rt"),
        QImage("../icons/VC_rd_up"),
        QImage("../icons/VC_rd_dn"),
    };
    QVector<QVector<QImage>> m_robotSkin{m_white, m_green, m_yellow, m_red};

    QPoint m_targetPosition;
    QPoint m_robotPosition;
    QVector<QPoint> m_batteries;

    bool m_inGame;
    bool m_scoreIncrease;

    int m_repaintTimerId;
    int m_animationTimerId;
    int m_score{0};
    int m_level{1};
    int m_energy;
    int m_steps;
    int m_trueWaySteps;

    QStack<State> m_states;

    void timerEvent(QTimerEvent *event)  override;
    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

    int getProcentEnergy();
    int getScore();
    int getStates();
    int getSteps();
    int getTrueWaySteps();

    void initRobot();
    void findTrueWay();
    QVector<QPoint> getWallsNeighbours(QPoint current, QSet<QPoint> cells);

    void locateSelf();
    void locateTarget();
    void locateBattery();    

    bool checkWall(QPoint dest);
    void checkTarget();
    void checkBattery();
    void checkEnergy();

    bool moveRobot();
    void updateScore(QKeyEvent *keyEvent=nullptr);
    void doStep(QKeyEvent *event=nullptr);
    void setState(State curState);
    void stepBack();

    void drawMaze();
    void drawRobot();
    void drawTarget();
    void drawBattery();

    void levelDone();
    void gameOver();
};



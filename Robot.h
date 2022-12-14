#pragma once

#include <iostream>
#include <memory>
#include <QPoint>
#include <QMap>
#include "Maze.h"
#include <QObject>
#include <QStack>

class Robot : public Maze{
    Q_OBJECT

public:
    Robot();
    ~Robot();

signals:
    void energyChanged(int energy);
    void scoreChanged(int score);
    void levelChanged(int level);

public slots:
    void initRobot();
    void checkEnergy();

private:
    static const int T_DELAY = 30;
    static const int A_DELAY = 300;

    enum Directions{
        left, right, up, down
    } m_dest;
    enum Colors{
        white, green, yellow, red
    }m_curColor, m_tmpColor;

    QPixmap m_batteryPM{"../icons/battery"};
    QPixmap m_targetPM{"../icons/target"};
    QVector<QPixmap> m_white{
        QPixmap("../icons/VC_wt_lt"),
        QPixmap("../icons/VC_wt_rt"),
        QPixmap("../icons/VC_wt_up"),
        QPixmap("../icons/VC_wt_dn"),
    };
    QVector<QPixmap> m_green{
        QPixmap("../icons/VC_gr_lt"),
        QPixmap("../icons/VC_gr_rt"),
        QPixmap("../icons/VC_gr_up"),
        QPixmap("../icons/VC_gr_dn"),
    };
    QVector<QPixmap> m_yellow{
        QPixmap("../icons/VC_yw_lt"),
        QPixmap("../icons/VC_yw_rt"),
        QPixmap("../icons/VC_yw_up"),
        QPixmap("../icons/VC_yw_dn"),
    };
    QVector<QPixmap> m_red{
        QPixmap("../icons/VC_rd_lt"),
        QPixmap("../icons/VC_rd_rt"),
        QPixmap("../icons/VC_rd_up"),
        QPixmap("../icons/VC_rd_dn"),
    };
    QVector<QVector<QPixmap>> m_scin{
        m_white,
        m_green,
        m_yellow,
        m_red
    };

    struct State{
        QPoint POSITION;
        QVector<QPoint> BATTERY;
        int SCORE;
        int ENERGY;
        int STEPS;
        Directions DESTINATION;
        Colors CURRENT_COLOR;
        Colors TEMPORARY_COLOR;

        State()=default;
        State(QPoint pos, QVector<QPoint> bat, int scr, int enrg, int stps, Directions dest, Colors cur, Colors tmp){
            POSITION = pos;
            BATTERY = bat;
            SCORE = scr;
            ENERGY = enrg;
            STEPS = stps;
            DESTINATION = dest;
            CURRENT_COLOR = cur;
            TEMPORARY_COLOR = tmp;

        }
    };


    bool m_inGame;
    int m_repaintTimerId;
    int m_animTimerId;

    QPoint m_target;
    QPoint m_pos;
    QVector<QPoint> m_battery;
    int m_score{0};
    int m_level{1};
    int m_energy;
    int m_steps;
    int m_trueWay;
    QStack<State> m_states;



    void timerEvent(QTimerEvent *event)  override;
    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event)  override;


    int getEnergy();
    int getScore();
    int getStates();
    int getSteps();
    int getTrueWay();

    void findTrueWay();
    void locateSelf();
    void locateTarget();
    void locateBattery();
    bool moveRobot();

    bool checkWall(QPoint dest);
    void checkTarget();
    void checkBattery();    

    void levelDone();
    void gameOver();
    void updateScore(QKeyEvent *keyEvent=nullptr);
    void doStep(QKeyEvent *event=nullptr);
    void stepBack();
    void setState(State curState);
    QVector<QPoint> getWallsNeighbours(QPoint current, QSet<QPoint> cells);


    void drawMaze();
    void drawRobot();
    void drawTarget();
    void drawBattery();
};



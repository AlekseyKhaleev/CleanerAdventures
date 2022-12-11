#pragma once

#include <iostream>
#include <memory>
#include <QPoint>
#include <QMap>
#include "Maze.h"
#include <QObject>

class Robot : public Maze{
//    Q_OBJECT

private:
    QString m_name;
    int m_score{0};

    int m_energy;
    int m_steps;
    int m_shortWay;
    static const int T_DELAY = 30;
    static const int A_DELAY = 300;
    int m_anim_timer;
    QVector<QPoint> m_battery;
    QPoint m_target;
    QPoint m_pos;
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


    void timerEvent(QTimerEvent *event)  override;
    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event)  override;

    void locateSelf();
    void locateTarget();
    void locateBattery();
    void initRobot();
    bool moveRobot();
    bool checkWall(QPoint dest);
    void checkTarget();
    void checkBattery();
    void checkEnergy();
    void drawRobot();
    void drawTarget();
    void drawBattery();
    void gameOver();
    void updateScore();
    void findShortWay();

    bool (*ActiveState)()= nullptr; // указатель на активное состояние автомата

    void SetState(bool (*state)());
    void Update();

    static bool wait();
    static bool analyze();
    static bool turn();
    static bool exit();
    static bool g_left();
    static bool g_right();

public:
//    QPoint SigHandle(signal sig) override;
    Robot();           // открытый конструктор
    ~Robot() override; // открытый деструктор
    int getEnergy();
    QString getName();
    int getScore();
    int m_robTimer;
};



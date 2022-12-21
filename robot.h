#pragma once

#include <QImage>
#include <QMap>
#include <QObject>
#include <QPoint>
#include <QStack>
#include "maze.h"
#include <iostream>
#include <memory>

//inline uint qHash(const QPoint &key) { return (key.x() << 16) + key.y(); }

class Robot : public Maze{
    Q_OBJECT


public:
    Robot();
    ~Robot() override;

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

    QImage *m_batteryImage;
    QImage *m_targetImage;
    QVector<QImage*> m_white;
    QVector<QImage*> m_green;
    QVector<QImage*> m_yellow;
    QVector<QImage*> m_red;
    QVector<QVector<QImage*>> m_robotSkin{m_white, m_green, m_yellow, m_red};
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

    int getPercentEnergy() const;
    void initRobot();
    void findTrueWay();
    static QVector<QPoint> getWallsNeighbours(QPoint current, const QSet<QPoint>& cells);

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
    void setState(const State& curState);
    void stepBack();

    void drawMaze();
    void drawRobot();
    void drawTarget();
    void drawBattery();

    void levelDone();
    void gameOver();
};



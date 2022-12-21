#pragma once

#include <QKeyEvent>
#include <QObject>

#include "RobotModel.h"
#include "MazeModel.h"

class Controller: public QObject {
    Q_OBJECT
signals:
    void levelLost();
    void levelDone();

    void resetMaze();
    void resetRobot();

    void destinationChanged(Robot::Directions dir);
    void positionChanged(QPoint tar_pos);
    void energyChanged(int percEnergy);
    void stepsChanged(int value);
    void scoreChanged(int value);
    void curColorChanged(Robot::Colors value);
    void tmpColorChanged(Robot::Colors value);
    void batteryLocated(QPoint value);
    void scoreIncreaseChanged(bool value);
    void batteryFound(QPoint value);
    void robotStateChanged(Robot::Model state);
    void mazeStateChanged(Maze::Model state);
    void skinAnimated();

public slots:
    void keyEventAction(QKeyEvent event);
    void updateRobotModel(Robot::Model model);
    void updateMazeModel(Maze::Model model);
    void startGame();
    void endGame();
    void clearMemory();

public:
    Controller(Robot::Model robotModel, Maze::Model mazeModel, QObject *parent= nullptr);
    ~Controller() override;
    friend Robot::RobotModel;
private:

    static const int ANIMATION_DELAY = 300;
    int m_animationTimerId;

    void timerEvent(QTimerEvent *event)  override;

    struct State
    {
        Robot::Model robotState;
        Maze::Model mazeState;
        State() = default;
        State(QPoint position,
              QVector<QPoint> batteries,
              int score,
              int steps,
              Robot::Directions destination,
              Robot::Colors current,
              Robot::Colors temp)
        {
            robotState.robotPosition = position;
            robotState.score = score;
            robotState.steps = steps;
            robotState.robotDestination = destination;
            robotState.curColor = current;
            robotState.tmpColor = temp;
            mazeState.batteries = batteries;
        }
    };
    QStack<State> m_states;

    Robot::Model m_robotModel;
    Maze::Model m_mazeModel;

    void checkTarget();

    int getPercentEnergy() const;

    bool moveRobot();

    void doStep(QKeyEvent *event= nullptr);

    void updateScore(QKeyEvent *event);

    void checkEnergy();

    void locateBattery();

    QPoint getRandDot();

    bool checkWall(QPoint dest);

    void checkBattery();

    void stepBack();
};



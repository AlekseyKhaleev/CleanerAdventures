#pragma once

#include <QKeyEvent>
#include <QObject>

#include "RobotModel.h"

class RobotController: public QObject {
    Q_OBJECT
signals:
//    void modelChanged(RobotModel::Model currentModel);
    void inGameChanged(bool value);
    void destinationChanged(Robot::Directions dir);
    void robotPositionChanged(QPoint tar_pos);
    void robotEnergyChanged(int value);
    void robotStepsChanged(int value);
    void robotScoreChanged(int value);
    void curColorChanged(Robot::Colors value);
    void tmpColorChanged(Robot::Colors value);
    void batteryLocated(QPoint value);
    void scoreIncreaseChanged(bool value);
    void batteryFinded(QPoint value);
    void robotStateChanged(Robot::Model state);
    void mazeStateChanged(Maze::Model state);
    void skinAnimated();

public slots:
    void keyEventAction(QKeyEvent event);

public:
    RobotController(const Robot::Model &robotModel, const Maze::Model &mazeModel, QObject *parent= nullptr);
    ~RobotController() override;
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
              int energy,
              int steps,
              Robot::Directions destination,
              Robot::Colors current,
              Robot::Colors temp)
        {
            robotState.robotPosition = position;
            robotState.score = score;
            robotState.energy = energy;
            robotState.steps = steps;
            robotState.robotDestination = destination;
            robotState.curColor = current;
            robotState.tmpColor = temp;
            mazeState.batteries = batteries;
        }
    };
    QStack<State> m_states;

    const Robot::Model *m_robotModel;
    const Maze::Model *m_mazeModel;

    void checkTarget();

    [[nodiscard]] int getPercentEnergy() const;

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



#pragma once

#include <QKeyEvent>
#include <QObject>

#include "robot.h"

class RobotController: public QObject {
    Q_OBJECT
signals:
//    void modelChanged(RobotModel::Model currentModel);
    void inGameChanged(bool value);
    void destinationChanged(Directions dir);
    void robotPositionChanged(QPoint tar_pos);
    void robotEnergyChanged(int value);
    void robotStepsChanged(int value);
    void robotScoreChanged(int value);
    void curColorChanged(RobotModel::Colors value);
    void tmpColorChanged(RobotModel::Colors value);
    void batteryLocated(QPoint value);
    void scoreIncreaseChanged(bool value);
    void batteryFinded(QPoint value);
    void robotStateChanged(RobotModel::Model state);
    void mazeStateChanged(MazeModel::Model state);

public slots:
    void keyEventAction(QKeyEvent event);

public:
    RobotController(const RobotModel::Model &robotModel, const MazeModel::Model &mazeModel, QObject *parent= nullptr);
    ~RobotController() override;
private:
    struct State
    {
        RobotModel::Model robotState;
        MazeModel::Model mazeState;
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
    RobotModel::Model m_robotModel;
    MazeModel::Model m_mazeModel;

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



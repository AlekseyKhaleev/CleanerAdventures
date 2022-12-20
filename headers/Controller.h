#pragma once

#include <QKeyEvent>
#include <QObject>

#include "RobotModel.h"

class Controller: public QObject {
    Q_OBJECT
signals:
    void gameLosed();
    void gameWon();

    void resetMaze(int levelIncrease);
    void resetRobot(Maze::Model model);

    void destinationChanged(Robot::Directions dir);
    void PositionChanged(QPoint tar_pos);
    void EnergyChanged(int value);
    void StepsChanged(int value);
    void ScoreChanged(int value);
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
    void updateRobotModel(Robot::Model model);
    void updateMazeModel(Maze::Model model);
    void startGame(int levelIncrease);
    void endGame();

public:
    Controller(const Robot::Model &robotModel, const Maze::Model &mazeModel, QObject *parent= nullptr);
    ~Controller() override;
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

    Robot::Model m_robotModel;
    Maze::Model m_mazeModel;

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



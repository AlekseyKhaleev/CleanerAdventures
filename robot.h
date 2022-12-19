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
namespace RobotModel{
    enum Directions {
        LEFT, RIGHT, UP, DOWN
    };

    enum Colors{
        WHITE, GREEN, YELLOW, RED
    };


    struct Model {
        bool inGame, scoreIncrease;
        Colors curColor, tmpColor;
        int dotWidth, dotHeight, score{0}, energy, steps;
        Directions robotDestination;
        QPoint robotPosition;
    };
}

namespace MazeModel{

    struct Model{

        QSet<QPoint> walls, cells;
        QVector<QPoint> batteries;
        QPoint targetPosition;
        int level{1}, trueWaySteps, fieldWidth, fieldHeight;
    };
}

using namespace RobotModel;

class Robot : public Maze{
    Q_OBJECT


public:
    explicit Robot(QWidget *parent = nullptr);
    ~Robot() override;
    RobotModel::Model getRobotModel();
    MazeModel::Model getMazeModel();

signals:
    void energyChanged(int energy);
    void scoreChanged(int score);
    void levelChanged(int level);
    void modelChanged(RobotModel::Model robotState);

public slots:
    void setInGame(bool value);
    void setDestination(Directions dir);
    void setRobotPosition(QPoint tar_pos);
    void setRobotEnergy(int value);
    void setRobotSteps(int value);
    void setRobotScore(int value);
    void setCurColor(RobotModel::Colors value);
    void setTmpColor(RobotModel::Colors value);
    void addBattery(QPoint value);
    void delBattery(QPoint value);
    void setScoreIncrease(bool value);
    void setRobotState(RobotModel::Model state);
    void setMazeState(MazeModel::Model state);


private:

    RobotModel::Model *m_robotState;
    MazeModel::Model *m_mazeState;
    QImage *m_batteryImage;
    QImage *m_targetImage;


    int m_repaintTimerId;

    void timerEvent(QTimerEvent *event)  override;
//    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;


    void initRobot();
    void findTrueWay();
    static QVector<QPoint> getWallsNeighbours(QPoint current, const QSet<QPoint>& cells);

    void locateSelf();
    void locateTarget();
    void drawMaze();
    void drawTarget();
    void drawBattery();

//    void levelDone();
//    void gameOver();
};



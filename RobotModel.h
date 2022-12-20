#pragma once

#include <QImage>
#include <QMap>
#include <QObject>
#include <QPoint>
#include <QStack>

#include <iostream>
#include <memory>

#include "MazeModel.h"

//inline uint qHash(const QPoint &key) { return (key.x() << 16) + key.y(); }

namespace Robot {
    enum Directions {
        LEFT, RIGHT, UP, DOWN
    };

    enum Colors {
        WHITE, GREEN, YELLOW, RED
    };


    struct Model {
        bool inGame, scoreIncrease;
        Colors curColor, tmpColor;
        int dotWidth, dotHeight, score{0}, energy, steps, trueWaySteps;
        static const int DOT_SIDE{34};
        Directions robotDestination{UP};
        QPoint robotPosition{1,1};
    };


    class RobotModel : public QObject {
    Q_OBJECT


    public:

        RobotModel(const Maze::Model &maze, QObject *parent = nullptr);

        ~RobotModel() override;

        Model getRobotModel();

    signals:

        void modelChanged();

    public slots:

        void setInGame(bool value);

        void setDestination(Robot::Directions dir);

        void setRobotPosition(QPoint tar_pos);

        void setRobotEnergy(int value);

        void setRobotSteps(int value);

        void setRobotScore(int value);

        void setCurColor(Robot::Colors value);

        void setTmpColor(Robot::Colors value);

        void setScoreIncrease(bool value);

        void setRobotState(Robot::Model state);

        void animateSkin();




    private:

        Model             *m_robotState;
        const Maze::Model *m_mazeState;

        void initRobot();

        void findTrueWay();

        static QVector<QPoint> getWayNeighbours(QPoint current, const QSet<QPoint> &cells);

//    void levelDone();
//    void gameOver();
    };
}


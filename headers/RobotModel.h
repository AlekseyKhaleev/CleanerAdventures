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
        bool scoreIncrease{};
        Colors curColor{}, tmpColor{};
        int score{0}, energy{}, steps{}, trueWaySteps{};
        static const int DOT_SIDE{34};
        Directions robotDestination{UP};
        QPoint robotPosition;
    };


    class RobotModel : public QObject {
    Q_OBJECT


    public:

        explicit RobotModel(const Maze::Model &maze, QObject *parent = nullptr);

        ~RobotModel() override;

        Model getRobotModel();

    signals:

        void modelChanged(Robot::Model model);

    public slots:

        void initRobot(Maze::Model maze);

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

        Model *m_robotState;

        Maze::Model m_mazeState;

        void findTrueWay();

        static QVector<QPoint> getWayNeighbours(QPoint current, const QSet<QPoint> &cells);

//    void levelDone();
//    void gameOver();
    };
}

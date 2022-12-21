#pragma once

#include <QImage>
#include <QMap>
#include <QObject>
#include <QPoint>
#include <QStack>

#include <iostream>
#include <memory>


//inline uint qHash(const QPoint &key) { return (key.x() << 16) + key.y(); }


namespace Robot {
    enum Directions {
        LEFT, RIGHT, UP, DOWN
    };

    enum Colors {
        WHITE, GREEN, YELLOW, RED
    };


    struct Model {

        static const int DOT_SIDE{34};
        bool scoreIncrease{};
        Colors curColor{}, tmpColor{};
        int score{0}, steps{};
        Directions robotDestination{};
        QPoint robotPosition;
    };


    class RobotModel : public QObject {
    Q_OBJECT


    public:

        explicit RobotModel(QObject *parent = nullptr);

        ~RobotModel() override;

        Robot::Model getModel();

    signals:

        void modelChanged(Robot::Model model);

    public slots:

        void initRobot();

        void setDestination(Robot::Directions dir);

        void setRobotPosition(QPoint tar_pos);

        void setRobotSteps(int value);

        void setRobotScore(int value);

        void setCurColor(Robot::Colors value);

        void setTmpColor(Robot::Colors value);

        void setScoreIncrease(bool value);

        void setRobotState(Robot::Model state);

        void animateSkin();

    private:

        Model *m_robotState;

    };
}


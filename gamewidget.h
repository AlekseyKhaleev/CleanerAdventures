#pragma once

#include <QObject>
#include <QLabel>
#include <QLCDNumber>
#include <QWidget>

#include "RobotModel.h"
#include "Controller.h"
#include "RobotView.h"

#include "MazeModel.h"
#include "MazeView.h"

class GameWidget : public QWidget
{
Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = nullptr);
private:
    static QLabel *createLabel(const QString &text);
    Robot::RobotModel *m_robotModel;
    Controller *m_controller;
    RobotView *m_robotView;

    Maze::MazeModel *m_mazeModel;
    MazeView *m_mazeView;

    QWidget *m_energyStatus;
    QLCDNumber *m_levelLcd;
    QLCDNumber *m_scoreLcd;
};


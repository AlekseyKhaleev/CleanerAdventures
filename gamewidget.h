#pragma once

#include <QObject>
#include <QLabel>
#include <QLCDNumber>
#include <QWidget>

#include "Controller.h"
#include "EnergyView.h"
#include "MazeModel.h"
#include "MazeView.h"
#include "RobotModel.h"
#include "RobotView.h"
#include "LevelView.h"
#include "ScoreView.h"


class GameWidget : public QWidget
{
Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = nullptr);
private:
    static QLabel *createLabel(const QString &text);

    Robot::RobotModel *m_robotModel;
    RobotView *m_robotView;

    Maze::MazeModel *m_mazeModel;
    MazeView *m_mazeView;

    Controller *m_controller;
    EnergyView *m_energyView;

    LevelView *m_levelView;
    ScoreView *m_scoreView;
};


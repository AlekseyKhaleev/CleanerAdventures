#pragma once

#include <QLabel>
#include <QLCDNumber>
#include <QMessageBox>
#include <QObject>
#include <QWidget>

#include "Controller.h"
#include "GameOverView.h"
#include "EnergyView.h"
#include "LCDView.h"
#include "MazeModel.h"
#include "MazeView.h"
#include "RobotModel.h"
#include "RobotView.h"
#include "MenuWidget.h"


class GameWidget : public QWidget
{
Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = nullptr);

signals:
    void returnClicked(int button=Menu::RETURN);

private:
    static QLabel *createLabel(const QString &text);

    Robot::RobotModel *m_robotModel;
    RobotView *m_robotView;

    Maze::MazeModel *m_mazeModel;
    MazeView *m_mazeView;

    Controller *m_controller;
    EnergyView *m_energyView;

    LCDView *m_levelView;
    LCDView *m_scoreView;

     GameOverView *m_gameOverView;


};


#pragma once

#include <QLabel>
#include <QLCDNumber>
#include <QMessageBox>
#include <QObject>
#include <QWidget>

#include "game/Controller.h"
#include "game/GameOverView.h"
#include "game/EnergyView.h"
#include "game/LCDView.h"
#include "game/LogView.h"
#include "game/MazeModel.h"
#include "game/MazeView.h"
#include "game/RobotModel.h"
#include "game/RobotView.h"
#include "MenuWidget.h"


class GameWidget : public QWidget
{
Q_OBJECT
public:
    explicit GameWidget(QString name, QWidget *parent = nullptr);

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

    LogView *m_logView;

     GameOverView *m_gameOverView;


};


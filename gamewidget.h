#pragma once

#include <QObject>
#include <QLabel>
#include <QLCDNumber>
#include <QWidget>

#include "robot.h"
#include "RobotController.h"
#include "RobotView.h"

class GameWidget : public QWidget
{
Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = nullptr);
private:
    static QLabel *createLabel(const QString &text);
    Robot *m_robot;
    RobotController *m_robotController;
    RobotView *m_robotView;

    QWidget *m_energyStatus;
    QLCDNumber *m_levelLcd;
    QLCDNumber *m_scoreLcd;
};


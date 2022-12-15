#pragma once

#include <QObject>
#include <QWidget>
#include <QLCDNumber>
#include <QLabel>
#include "Robot.h"

class GameWidget : public QWidget
{
Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = nullptr);
private:
    QLabel *createLabel(const QString &text);
    Robot *m_robot;
    QWidget *m_energyStatus;
    QLCDNumber *m_levelLcd;
    QLCDNumber *m_scoreLcd;
};


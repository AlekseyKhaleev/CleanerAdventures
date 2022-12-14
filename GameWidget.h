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
    Robot *robot;
    QWidget *energyStatus;
    QLCDNumber *levelLcd;
    QLCDNumber *scoreLcd;
};


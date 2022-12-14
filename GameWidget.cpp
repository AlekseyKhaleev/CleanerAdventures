#include "GameWidget.h"
#include "EnergyWidget.h"

#include <QLCDNumber>
#include <QCoreApplication>
#include <QLayout>

GameWidget::GameWidget(QWidget *parent)
    : QWidget{parent}, robot(new Robot), energyStatus(new EnergyWidget)
{
    this->setStyleSheet("QWidget {background-color: black; color: white;}");

    robot->setFocusPolicy(Qt::StrongFocus);
    robot->setStyleSheet("Robot {background-color: white; color: black;}");

    scoreLcd = new QLCDNumber(4);
    scoreLcd->setSegmentStyle(QLCDNumber::Filled);
    levelLcd = new QLCDNumber(4);
    levelLcd->setSegmentStyle(QLCDNumber::Filled);

    connect(robot, SIGNAL(energyChanged(int)),
            energyStatus, SLOT(setEnergyStatus(int)));
    connect(robot, &Robot::scoreChanged,
            scoreLcd, qOverload<int>(&QLCDNumber::display));
    connect(robot, &Robot::levelChanged,
            levelLcd, qOverload<int>(&QLCDNumber::display));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(createLabel(tr("ENERGY")), 0, 0);
    layout->addWidget(energyStatus,1,0,3,1);
    layout->addWidget(createLabel(tr("LEVEL")), 0, 1);
    layout->addWidget(levelLcd, 1, 1, 3, 1);
    layout->addWidget(createLabel(tr("SCORE")), 0, 2);
    layout->addWidget(scoreLcd, 1, 2, 3, 1);
    layout->addWidget(createLabel(tr("")), 5, 0);
    layout->addWidget(robot, 6, 0, 20, 3);

    setLayout(layout);
    setWindowTitle(tr("Robot"));
}
QLabel *GameWidget::createLabel(const QString &text)
{
    QLabel *label = new QLabel(text);
    label->setWindowFlag(Qt::FramelessWindowHint);
    label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    return label;
}

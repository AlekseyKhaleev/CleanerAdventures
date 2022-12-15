#include "gamewidget.h"
#include "EnergyWidget.h"
#include "Robot.h"

#include <QLCDNumber>
#include <QCoreApplication>
#include <QLayout>

GameWidget::GameWidget(QWidget *parent)
        : QWidget{parent}, m_robot(new Robot), m_energyStatus(new EnergyWidget)
{
    this->setStyleSheet("QWidget {background-color: black; color: white;}");

    m_robot->setFocusPolicy(Qt::StrongFocus);
    m_robot->setStyleSheet("Robot {background-color: white; color: black;}");

    m_scoreLcd = new QLCDNumber(4);
    m_scoreLcd->setSegmentStyle(QLCDNumber::Filled);
    m_levelLcd = new QLCDNumber(4);
    m_levelLcd->setSegmentStyle(QLCDNumber::Filled);

    connect(m_robot, SIGNAL(energyChanged(int)),
            m_energyStatus, SLOT(setEnergyStatus(int)));
    connect(m_robot, &Robot::scoreChanged,
            m_scoreLcd, qOverload<int>(&QLCDNumber::display));
    connect(m_robot, &Robot::levelChanged,
            m_levelLcd, qOverload<int>(&QLCDNumber::display));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(createLabel(tr("<b>ENERGY</b>")), 0, 0, 2, 1);
    layout->addWidget(m_energyStatus,2,0,3,1);
    layout->addWidget(createLabel(tr("<b>LEVEL</b>")), 0, 1, 2, 1);
    layout->addWidget(m_levelLcd, 2, 1, 3, 1);
    layout->addWidget(createLabel(tr("<b>SCORE</b>")), 0, 2, 2, 1);
    layout->addWidget(m_scoreLcd, 2, 2, 3, 1);
    layout->addWidget(m_robot, 6, 0, 20, 3);

    setLayout(layout);
    setWindowTitle(tr("Robot"));
}
QLabel *GameWidget::createLabel(const QString &text)
{
    QLabel *label = new QLabel(text);
    label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    return label;
}

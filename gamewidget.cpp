#include "gamewidget.h"

#include <QCoreApplication>
#include <QLayout>
#include <QLCDNumber>
#include <QStackedLayout>

#include "energywidget.h"
#include "RobotModel.h"

GameWidget::GameWidget(QWidget *parent):
QWidget{parent},
m_robot(new RobotModel),
m_robotController(new RobotController{m_robot->getRobotModel(), m_robot->getMazeModel()}),
m_robotView(new RobotView{m_robot->getRobotModel()}),
m_energyStatus(new EnergyWidget)
{
    this->setStyleSheet("QWidget {background-color: black; color: WHITE;}");

    m_robotView->setFocusPolicy(Qt::StrongFocus);
    m_robot->setStyleSheet("RobotModel {background-color: WHITE; color: black;}");

    m_scoreLcd = new QLCDNumber(4);
    m_scoreLcd->setSegmentStyle(QLCDNumber::Filled);
    m_levelLcd = new QLCDNumber(4);
    m_levelLcd->setSegmentStyle(QLCDNumber::Filled);

    connect(m_robotView, SIGNAL(keyHandled(QKeyEvent)),
            m_robotController, SLOT(keyEventAction(QKeyEvent)));
    connect(m_robot, SIGNAL(modelChanged()),
            m_robotView, SLOT(repaint()));
    connect(m_robotController, SIGNAL(inGameChanged(bool)),
            m_robot, SLOT(setInGame(bool)));
    connect(m_robotController, SIGNAL(robotScoreChanged(int)),
            m_robot, SLOT(setRobotScore(int)));
    connect(m_robotController, SIGNAL(tmpColorChanged(RobotModel::Colors)),
            m_robot, SLOT(setTmpColor(RobotModel::Colors)));
    connect(m_robotController, SIGNAL(curColorChanged(RobotModel::Colors)),
            m_robot, SLOT(setCurColor(RobotModel::Colors)));
    connect(m_robotController, SIGNAL(robotEnergyChanged(int)),
            m_robot, SLOT(setRobotEnergy(int)));
    connect(m_robotController, SIGNAL(batteryFinded(QPoint)),
            m_robot, SLOT(delBattery(QPoint)));
    connect(m_robotController, SIGNAL(batteryLocated(QPoint)),
            m_robot, SLOT(addBattery(QPoint)));
    connect(m_robotController, SIGNAL(destinationChanged(Directions)),
            m_robot, SLOT(setDestination(Directions)));
    connect(m_robotController, SIGNAL(mazeStateChanged(MazeModel::Model)),
            m_robot, SLOT(setMazeState(MazeModel::Model)));
    connect(m_robotController, SIGNAL(robotPositionChanged(QPoint)),
            m_robot, SLOT(setRobotPosition(QPoint)));
    connect(m_robotController, SIGNAL(robotStateChanged(RobotModel::Model)),
            m_robot, SLOT(setRobotState(RobotModel::Model)));
    connect(m_robotController, SIGNAL(robotStepsChanged(int)),
            m_robot, SLOT(setRobotSteps(int)));
    connect(m_robotController, SIGNAL(scoreIncreaseChanged(bool)),
            m_robot, SLOT(setScoreIncrease(bool)));

    connect(m_robot, SIGNAL(energyChanged(int)),
            m_energyStatus, SLOT(setEnergyStatus(int)));
    connect(m_robot, &RobotModel::scoreChanged,
            m_scoreLcd, qOverload<int>(&QLCDNumber::display));
    connect(m_robot, &RobotModel::levelChanged,
            m_levelLcd, qOverload<int>(&QLCDNumber::display));

    auto gameLay = new QStackedLayout;
    gameLay->setStackingMode(QStackedLayout::StackAll);
    gameLay->addWidget(m_robot);
    gameLay->addWidget(m_robotView);

    auto *layout = new QGridLayout;
    layout->addWidget(createLabel(tr("<b>ENERGY</b>")), 0, 0, 2, 1);
    layout->addWidget(m_energyStatus,2,0,3,1);
    layout->addWidget(createLabel(tr("<b>LEVEL</b>")), 0, 1, 2, 1);
    layout->addWidget(m_levelLcd, 2, 1, 3, 1);
    layout->addWidget(createLabel(tr("<b>SCORE</b>")), 0, 2, 2, 1);
    layout->addWidget(m_scoreLcd, 2, 2, 3, 1);
//    layout->addWidget(m_robot, 6, 0, 20, 3);
    layout->addLayout(gameLay, 6, 0, 20, 3);

    setLayout(layout);
    setWindowTitle(tr("RobotModel"));
}

QLabel *GameWidget::createLabel(const QString &text){
    auto *label = new QLabel(text);
    label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    return label;
}

#include "RobotModel.h"



#include <QKeyEvent>
#include <QStyleOption>
#include <QtGui>
#include <QVector>

#include "MazeModel.h"



using namespace Robot;

//*****************************************************

//Constructor
RobotModel::RobotModel(QObject *parent):
QObject(parent),
m_robotState(new Model)
{
    initRobot();
}

//Destructor
RobotModel::~RobotModel(){
    delete m_robotState;
}

//*****************************************************

void RobotModel::initRobot(){
    m_robotState->robotDestination = UP;
    m_robotState->robotPosition = QPoint{1,1};
    m_robotState->scoreIncrease = true;
    m_robotState->curColor = GREEN;
    m_robotState->tmpColor = WHITE;
    m_robotState->steps = 0;
    emit modelChanged(*m_robotState);
}



void RobotModel::setRobotState(Robot::Model state){
    m_robotState->robotPosition = state.robotPosition;
    m_robotState->score = state.score;
    m_robotState->steps = state.steps;
    m_robotState->robotDestination = state.robotDestination;
    m_robotState->curColor = state.curColor;
    m_robotState->tmpColor = state.tmpColor;
    emit modelChanged(*m_robotState);
}


void RobotModel::setDestination(Robot::Directions dir) {
    m_robotState->robotDestination = dir;
    emit modelChanged(*m_robotState);
}

void RobotModel::setRobotPosition(QPoint tar_pos) {
    m_robotState->robotPosition = tar_pos;
    emit modelChanged(*m_robotState);
}


void RobotModel::setRobotSteps(int value) {
    m_robotState->steps = value;
    emit modelChanged(*m_robotState);
}

void RobotModel::setRobotScore(int value) {
    m_robotState->score = value;
    emit modelChanged(*m_robotState);
}

void RobotModel::setCurColor(Robot::Colors value) {
    m_robotState->curColor = value;
    emit modelChanged(*m_robotState);
}

void RobotModel::setTmpColor(Robot::Colors value) {
    m_robotState->tmpColor = value;
    emit modelChanged(*m_robotState);
}

void RobotModel::setScoreIncrease(bool value) {
    m_robotState->scoreIncrease = value;
    emit modelChanged(*m_robotState);
}

void RobotModel::animateSkin() {
    qSwap(m_robotState->curColor, m_robotState->tmpColor);
    emit modelChanged(*m_robotState);
}


Robot::Model RobotModel::getModel() {
    return *m_robotState;
}



//void RobotModel::setRobotEnergy(int value) {
//    m_robotState->energy = value;
//    emit modelChanged(*m_robotState);
//}







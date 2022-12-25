#include "RobotModel.h"



#include <QKeyEvent>
#include <QStyleOption>
#include <QtGui>
#include <QVector>
#include <utility>




using namespace Robot;

//*****************************************************

//Constructor
RobotModel::RobotModel(QString name, QObject *parent):
        QObject(parent),
        m_model(new Model)
{
    m_model->name = std::move(name);
    initRobot();
}

//Destructor
RobotModel::~RobotModel(){
    m_model->state = "exit";
    emit modelChanged(*m_model);

    delete m_model;
}

//*****************************************************

void RobotModel::initRobot(){
    m_model->state = "init";
    m_model->robotDestination = UP;
    m_model->robotPosition = QPoint{1, 1};
    m_model->scoreIncrease = true;
    m_model->curColor = GREEN;
    m_model->tmpColor = WHITE;
    m_model->steps = 0;
    m_model->highScore += m_model->score;
    emit modelChanged(*m_model);
}



void RobotModel::setModel(Robot::Model model){
    m_model->state = "step back";
    m_model->robotPosition = model.robotPosition;
    m_model->score = model.score;
    m_model->steps = model.steps;
    m_model->robotDestination = model.robotDestination;
    m_model->curColor = model.curColor;
    m_model->tmpColor = model.tmpColor;
    emit modelChanged(*m_model);
}


void RobotModel::setDestination(Robot::Directions dir) {
    m_model->state = "rotate";
    m_model->robotDestination = dir;
    emit modelChanged(*m_model);
}

void RobotModel::setRobotPosition(QPoint tar_pos) {
    m_model->state = "move";
    m_model->robotPosition = tar_pos;
    emit modelChanged(*m_model);
}


void RobotModel::setRobotSteps(int value) {
    m_model->steps = value;
    emit modelChanged(*m_model);
}

void RobotModel::setRobotScore(int value) {
    m_model->score = value;
    emit modelChanged(*m_model);
}

void RobotModel::setCurColor(Robot::Colors value) {
    m_model->curColor = value;
    emit modelChanged(*m_model);
}

void RobotModel::setTmpColor(Robot::Colors value) {
    m_model->tmpColor = value;
    emit modelChanged(*m_model);
}

void RobotModel::setScoreIncrease(bool value) {
    m_model->scoreIncrease = value;
    emit modelChanged(*m_model);
}

void RobotModel::animateSkin() {
    m_model->state = "wait";
    qSwap(m_model->curColor, m_model->tmpColor);
    emit modelChanged(*m_model);
}


Robot::Model RobotModel::getModel() {
    return *m_model;
}







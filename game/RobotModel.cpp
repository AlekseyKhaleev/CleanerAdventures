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
        QObject(parent)
//        m_model(new Model)
{
    m_model.name = std::move(name);
    initRobot();
}

//Destructor
RobotModel::~RobotModel()=default;
//    m_model->state = "exit";
//    emit modelChanged(*m_model);
//
//    delete m_model;
//}

//*****************************************************

void RobotModel::initRobot(){
    m_model.state = "init";
    m_model.robotDestination = UP;
    m_model.robotPosition = QPoint{1, 1};
    m_model.scoreIncrease = true;
    m_model.curColor = GREEN;
    m_model.tmpColor = WHITE;
    m_model.steps = 0;
    m_model.highScore += m_model.score;
    m_memory.clear();
    m_memory.push(m_model);

    emit modelChanged(m_model);
}



void RobotModel::stepBack(){

   if(!m_memory.isEmpty()){
      Model lastModel = m_memory.pop();
      if(lastModel.steps == m_model.steps){
         stepBack();
      }
      else
      {
         m_model.robotPosition = lastModel.robotPosition;
         m_model.robotDestination = lastModel.robotDestination;
         m_model.score = lastModel.score;
         m_model.steps = lastModel.steps;
         m_model.curColor = lastModel.curColor;
         m_model.tmpColor = lastModel.tmpColor;
         m_model.state = "step back";
         emit modelChanged(m_model);
      }
      if(m_memory.isEmpty()){
         m_memory.push(m_model);
      }
   }
}


void RobotModel::setDestination(Robot::Directions dir) {
    m_model.state = "rotate";
    m_model.robotDestination = dir;
    emit modelChanged(m_model);
}

void RobotModel::setRobotPosition(QPoint tar_pos) {
    m_model.state = "move";
    m_model.robotPosition = tar_pos;
    emit modelChanged(m_model);
}


void RobotModel::setRobotSteps(int value) {
    m_model.steps = value;
    m_memory.push(m_model);
    emit modelChanged(m_model);
}

void RobotModel::setRobotScore(int value) {
    m_model.score = value;
    emit modelChanged(m_model);
}

void RobotModel::setCurColor(Robot::Colors value) {
    m_model.curColor = value;
    emit modelChanged(m_model);
}

void RobotModel::setTmpColor(Robot::Colors value) {
    m_model.tmpColor = value;
    emit modelChanged(m_model);
}

void RobotModel::setScoreIncrease(bool value) {
    m_model.scoreIncrease = value;
    emit modelChanged(m_model);
}

void RobotModel::animateSkin() {
    m_model.state = "wait";
    qSwap(m_model.curColor, m_model.tmpColor);
    emit modelChanged(m_model);
}


Robot::Model RobotModel::getModel() {
    return m_model;
}







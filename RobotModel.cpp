#include "RobotModel.h"


#include <QPainter>
#include <QKeyEvent>
#include <QVector>
#include <QSet>
#include <QtGui>
#include <QMessageBox>
#include <QStyleOption>

#include "MazeModel.h"



using namespace Robot;

//*****************************************************

//Constructor
RobotModel::RobotModel(const Maze::Model &maze, QObject *parent):
QObject(parent),
m_robotState(new Model),
m_mazeState(&maze)
{

    initRobot();
}

//Destructor
RobotModel::~RobotModel(){
    delete m_robotState;
}

//*****************************************************

void RobotModel::initRobot(){

    m_robotState->inGame = true;
    m_robotState->scoreIncrease = true;
    m_robotState->curColor = GREEN;
    m_robotState->tmpColor = WHITE;
    m_robotState->steps = 0;
    findTrueWay();
    m_robotState->energy = m_robotState->trueWaySteps;
}




//    else if(m_energy != 0){
////        levelDone();
//    }
//    else{
////        gameOver();
//    }
//}

//void RobotModel::levelDone(){
//    killTimer(m_repaintTimerId);
//    killTimer(m_animationTimerId);
//    QMessageBox msgb;
//    msgb.setText("<p align='center'>Level done, great! </p>");
//    msgb.setInformativeText("<p align='center'>Wanna go next?</p>");
//    msgb.setStandardButtons(QMessageBox::Close | QMessageBox::Retry);
//    msgb.setDefaultButton(QMessageBox::Retry);
//    int ret = msgb.exec();
//    if (ret == QMessageBox::Retry) {
//        initMaze();
//        initRobot();
//        m_level++;
//        m_score += 100;
//    } else {
//        QCoreApplication::quit();
//    }
//}
//
//void RobotModel::gameOver(){
//
//    QMessageBox msgb;
//    msgb.setText("<p align='center'>Ohh no! You lose! </p>");
//    msgb.setInformativeText("<p align='center'>Wanna try again?</p>");
//    msgb.setStandardButtons(QMessageBox::Close | QMessageBox::Retry);
//    msgb.setDefaultButton(QMessageBox::Retry);
//    int ret = msgb.exec();
//    if (ret == QMessageBox::Retry){
//        initMaze();
//        initRobot();
//        m_score = 0;
//        m_level = 1;
//    }
//    else {
//        killTimer(m_repaintTimerId);
//        killTimer(m_animationTimerId);
//        QCoreApplication::quit();
//    }
//}





void RobotModel::findTrueWay(){
    m_robotState->trueWaySteps = 2;
    QSet<QPoint> cells;
    for (auto k: qAsConst(m_mazeState->cells)){
        cells.insert(k);
    }
    QPoint current = m_robotState->robotPosition;
    QVector<QPoint> neighbours;
    QStack<QPoint> way;
    cells.remove(current);
    while (current != m_mazeState->targetPosition) {
        neighbours = getWayNeighbours(current, cells);
        if(!neighbours.empty()){
            way.push(current);
            current = neighbours[rand()%neighbours.size()];
            cells.remove(current);
        }
        else if(!way.isEmpty()){
            current = way.pop();
        }
        else{break;}
    }
    m_robotState->trueWaySteps += way.size();
    for(int i=1;i<way.size()-1;i++){
        if((way[i-1].x()==way[i].x()&&way[i+1].y()==way[i].y())||(way[i-1].y()==way[i].y()&&way[i+1].x()==way[i].x())){
            m_robotState->trueWaySteps++;
        }
    }    
 }

void RobotModel::setRobotState(Model state){
    m_robotState->robotPosition = state.robotPosition;
    m_robotState->score = state.score;
    m_robotState->energy = state.energy;
    m_robotState->steps = state.steps;
    m_robotState->robotDestination = state.robotDestination;
    m_robotState->curColor = state.curColor;
    m_robotState->tmpColor = state.tmpColor;
    emit modelChanged();
}

QVector<QPoint> RobotModel::getWayNeighbours(QPoint current, const QSet<QPoint>& cells){
    QVector<QPoint> curNeighbours;
    current.rx()+=1;
    if(cells.contains(current)){
        curNeighbours.push_back(current);
    }
    current.rx()-=2;
    if(cells.contains(current)){
        curNeighbours.push_back(current);
    }
    current.rx()+=1;
    current.ry()+=1;
    if(cells.contains(current)){
        curNeighbours.push_back(current);
    }
    current.ry()-=2;
    if(cells.contains(current)){
        curNeighbours.push_back(current);
    }
    return curNeighbours;
}

void RobotModel::setInGame(bool value) {
    m_robotState->inGame = value;
    emit modelChanged();
}

void RobotModel::setDestination(Directions dir) {
    m_robotState->robotDestination = dir;
    emit modelChanged();
}

void RobotModel::setRobotPosition(QPoint tar_pos) {
    m_robotState->robotPosition = tar_pos;
    emit modelChanged();
}

void RobotModel::setRobotEnergy(int value) {
    m_robotState->energy = value;
    emit modelChanged();
}

void RobotModel::setRobotSteps(int value) {
    m_robotState->steps = value;
    emit modelChanged();
}

void RobotModel::setRobotScore(int value) {
    m_robotState->score = value;
    emit modelChanged();
}

void RobotModel::setCurColor(Colors value) {
    m_robotState->curColor = value;
    emit modelChanged();
}

void RobotModel::setTmpColor(Colors value) {
    m_robotState->tmpColor = value;
    emit modelChanged();
}

void RobotModel::setScoreIncrease(bool value) {
    m_robotState->scoreIncrease = value;
    emit modelChanged();
}


Model RobotModel::getRobotModel() {
    return *m_robotState;
}







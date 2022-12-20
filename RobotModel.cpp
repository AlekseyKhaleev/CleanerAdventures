#include "headers/RobotModel.h"



#include <QKeyEvent>
#include <QSet>
#include <QStyleOption>
#include <QtGui>
#include <QVector>

#include "headers/MazeModel.h"



using namespace Robot;

//*****************************************************

//Constructor
RobotModel::RobotModel(const Maze::Model &maze, QObject *parent):
QObject(parent),
m_robotState(new Model)
{
    initRobot(maze);
}

//Destructor
RobotModel::~RobotModel(){
    delete m_robotState;
}

//*****************************************************

void RobotModel::initRobot(Maze::Model maze){
    m_mazeState = maze;
    m_robotState->robotPosition = QPoint{1,1};
    m_robotState->scoreIncrease = true;
    m_robotState->curColor = GREEN;
    m_robotState->tmpColor = WHITE;
    m_robotState->steps = 0;
    findTrueWay();
    m_robotState->energy = m_robotState->trueWaySteps;
}


void RobotModel::findTrueWay(){
    m_robotState->trueWaySteps = 2;
    QSet<QPoint> cells;
    for (auto k: qAsConst(m_mazeState.cells)){
        cells.insert(k);
    }
    QPoint current = m_robotState->robotPosition;
    QVector<QPoint> neighbours;
    QStack<QPoint> way;
    cells.remove(current);
    while (current != m_mazeState.targetPosition) {
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

void RobotModel::setRobotState(Robot::Model state){
    m_robotState->robotPosition = state.robotPosition;
    m_robotState->score = state.score;
    m_robotState->energy = state.energy;
    m_robotState->steps = state.steps;
    m_robotState->robotDestination = state.robotDestination;
    m_robotState->curColor = state.curColor;
    m_robotState->tmpColor = state.tmpColor;
    emit modelChanged(*m_robotState);
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

void RobotModel::setDestination(Robot::Directions dir) {
    m_robotState->robotDestination = dir;
    emit modelChanged(*m_robotState);
}

void RobotModel::setRobotPosition(QPoint tar_pos) {
    m_robotState->robotPosition = tar_pos;
    emit modelChanged(*m_robotState);
}

void RobotModel::setRobotEnergy(int value) {
    m_robotState->energy = value;
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


Model RobotModel::getRobotModel() {
    return *m_robotState;
}

void RobotModel::animateSkin() {
    qSwap(m_robotState->curColor, m_robotState->tmpColor);
    emit modelChanged(*m_robotState);
}







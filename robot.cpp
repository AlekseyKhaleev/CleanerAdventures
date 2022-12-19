/*********************************************************************************************************************
* Данный модуль содержит определения иерархии классов, предназначенных для работы с таблицей данных отдела кадров
* (приложение Lab5-2)
*********************************************************************************************************************/

/* Подключение модулей */


#include <QPainter>
#include <QKeyEvent>
#include <QVector>
#include <QSet>
#include <QtGui>
#include <QMessageBox>
#include "robot.h"
#include <QStyleOption>
#include <QDebug>


using namespace RobotModel;

Robot::Robot(QWidget *parent):
Maze(parent),
m_targetImage(new  QImage(":/images/target.png")),
m_batteryImage(new QImage(":/images/battery.png")),
m_robotState(new Model),
m_mazeState(new MazeModel::Model)
{
    initRobot();
}

Robot::~Robot(){
    delete m_robotState;
    delete m_mazeState;
};

void Robot::initRobot(){
    m_robotState->inGame = true;
    m_robotState->scoreIncrease = true;
    m_robotState->curColor = GREEN;
    m_robotState->tmpColor = WHITE;
    if (!m_mazeState->batteries.empty()) {
        m_mazeState->batteries.clear();
    }
    m_mazeState->batteries.push_back(QPoint{-1, -1});
    m_robotState->steps = 0;
    m_robotState->energy = m_mazeState->trueWaySteps;
    locateSelf();
    locateTarget();
    findTrueWay();
    m_repaintTimerId = startTimer(0);
}

void Robot::timerEvent(QTimerEvent *event){
    if(event->timerId() == m_repaintTimerId){
        emit scoreChanged(m_robotState->score);
        emit levelChanged(m_mazeState->level);
//        emit energyChanged(getPercentEnergy());
        repaint();
    }
}

void Robot::paintEvent(QPaintEvent *event){
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);

    if(m_robotState->inGame){
        drawMaze();
        drawTarget();
        drawBattery();

    }
//    else if(m_energy != 0){
////        levelDone();
//    }
//    else{
////        gameOver();
//    }
}

/******************** Getters  *************/

/*************************************************************/


void Robot::locateSelf(){
    QVector<QPoint> angles{
        QPoint{1,1},
        QPoint{1, FIELD_HEIGHT-2},
        QPoint{FIELD_WIDTH-2, 1},
        QPoint{FIELD_WIDTH-2,FIELD_HEIGHT-2}
    };
    m_robotState->robotPosition = angles[rand() % angles.size()];
    m_robotState->robotDestination = Directions::UP;
}

void Robot::locateTarget()
{
    m_mazeState->targetPosition = m_robotState->robotPosition;
    if (m_mazeState->targetPosition.x() == 1) {
        m_mazeState->targetPosition.rx() = FIELD_WIDTH - 2;
    } else {
        m_mazeState->targetPosition.rx() = 1;
    }
    if (m_mazeState->targetPosition.y() == 1) {
        m_mazeState->targetPosition.ry() = FIELD_HEIGHT - 2;
    } else {
        m_mazeState->targetPosition.ry() = 1;
    }
}



void Robot::drawMaze(){
    QPainter qp(this);
    for(auto &w:qAsConst(m_walls)){
        qp.setBrush(Qt::black);
        qp.drawRect(w.x()*DOT_WIDTH, w.y()*DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT);
    }
}

void Robot::drawTarget()
{
    QPainter qp(this);
    qp.drawImage(QRect(m_mazeState->targetPosition.x() * DOT_WIDTH,
                       m_mazeState->targetPosition.y() * DOT_HEIGHT,
                       DOT_WIDTH,
                       DOT_HEIGHT),
                 *m_targetImage);
}

void Robot::drawBattery(){
    QPainter qp(this);
    for (auto &b : m_mazeState->batteries) {
        if (b.x() >= 0) {
            qp.drawImage(QRect(b.x() * DOT_WIDTH, b.y() * DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT),
                         *m_batteryImage);
        }
    }
 }











//void Robot::levelDone(){
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
//void Robot::gameOver(){
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





void Robot::findTrueWay(){
    m_mazeState->trueWaySteps = 2;
    QSet<QPoint> cells;
    for (auto k: qAsConst(m_cells)){
        cells.insert(k);
    }
    QPoint current = m_robotState->robotPosition;
    QVector<QPoint> neighbours;
    QStack<QPoint> way;
    cells.remove(current);
    while (current != m_mazeState->targetPosition) {
        neighbours = getWallsNeighbours(current, cells);
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
    m_mazeState->trueWaySteps += way.size();
    for(int i=1;i<way.size()-1;i++){
        if((way[i-1].x()==way[i].x()&&way[i+1].y()==way[i].y())||(way[i-1].y()==way[i].y()&&way[i+1].x()==way[i].x())){
            m_mazeState->trueWaySteps++;
        }
    }    
 }


void Robot::setMazeState(MazeModel::Model state){
    m_mazeState->batteries = state.batteries;

}


void Robot::setRobotState(RobotModel::Model state){
    m_robotState->robotPosition = state.robotPosition;
    m_robotState->score = state.score;
    m_robotState->energy = state.energy;
    m_robotState->steps = state.steps;
    m_robotState->robotDestination = state.robotDestination;
    m_robotState->curColor = state.curColor;
    m_robotState->tmpColor = state.tmpColor;
    emit modelChanged(*m_robotState);
}

QVector<QPoint> Robot::getWallsNeighbours(QPoint current, const QSet<QPoint>& cells){
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

void Robot::setInGame(bool value) {
    m_robotState->inGame = value;
    emit modelChanged(*m_robotState);
}

void Robot::setDestination(Directions dir) {
    m_robotState->robotDestination = dir;
    emit modelChanged(*m_robotState);
}

void Robot::setRobotPosition(QPoint tar_pos) {
    m_robotState->robotPosition = tar_pos;
    emit modelChanged(*m_robotState);
}

void Robot::setRobotEnergy(int value) {
    m_robotState->energy = value;
    emit modelChanged(*m_robotState);
}

void Robot::setRobotSteps(int value) {
    m_robotState->steps = value;
    emit modelChanged(*m_robotState);
}

void Robot::setRobotScore(int value) {
    m_robotState->score = value;
    emit modelChanged(*m_robotState);
}

void Robot::setCurColor(RobotModel::Colors value) {
    m_robotState->curColor = value;
    emit modelChanged(*m_robotState);
}

void Robot::setTmpColor(RobotModel::Colors value) {
    m_robotState->tmpColor = value;
    emit modelChanged(*m_robotState);
}

void Robot::addBattery(QPoint value) {
    m_mazeState->batteries.push_back(value);

}

void Robot::setScoreIncrease(bool value) {
    m_robotState->scoreIncrease = value;
    emit modelChanged(*m_robotState);
}

void Robot::delBattery(QPoint value) {
    m_mazeState->batteries.removeAll(value);
}

RobotModel::Model Robot::getRobotModel() {
    return *m_robotState;
}

MazeModel::Model Robot::getMazeModel() {
    return *m_mazeState;
}





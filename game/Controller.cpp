
#include "Controller.h"

#include <QCoreApplication>
#include <QKeyEvent>
#include <QTime>



Controller::Controller(Robot::Model robotModel, Maze::Model mazeModel, QObject *parent) :
    QObject(parent), m_robotModel(robotModel), m_mazeModel(mazeModel)
{
    m_animationTimerId = startTimer(ANIMATION_DELAY);
}

void Controller::timerEvent(QTimerEvent *event) {
    if(event->timerId()==m_animationTimerId){
        emit skinAnimated();
    }
}

void Controller::keyEventAction(int eventKey) {
    switch (eventKey) {
        case Qt::Key_Left: {
            if(m_robotModel.robotDestination!=Robot::Directions::LEFT){
                emit destinationChanged(Robot::Directions::LEFT);
                doStep();
            }
            break;
        }
        case Qt::Key_Right:{
            if(m_robotModel.robotDestination!=Robot::Directions::RIGHT){
                emit destinationChanged(Robot::Directions::RIGHT);
                doStep();
            }
            break;
        }
        case Qt::Key_Up:{
            if(m_robotModel.robotDestination!=Robot::Directions::UP){
                emit destinationChanged(Robot::Directions::UP);
                doStep();
            }
            break;
        }
        case Qt::Key_Down:{
            if(m_robotModel.robotDestination!=Robot::Directions::DOWN){
                emit destinationChanged(Robot::Directions::DOWN);
                doStep();
            }
            break;
        }
        case Qt::Key_Space:{
            if(moveRobot()){
                checkTarget();
                checkBattery();
                doStep(eventKey);
            }
            break;
        }
        case Qt::Key_Backspace:{
            emit stepBack();
            break;
        }
        case Qt::Key_Escape:{
            emit returnClicked();
            break;
        }
        default:break;
    }
}


void Controller::checkBattery()
{
    if (m_mazeModel.batteries.contains(m_robotModel.robotPosition)) {
        emit scoreIncreaseChanged(false);
        emit stepsChanged(0);
        emit energyChanged(getPercentEnergy());
        emit curColorChanged(Robot::GREEN);
        emit tmpColorChanged(Robot::WHITE);
        emit batteryFound(m_robotModel.robotPosition);
        emit scoreChanged(m_robotModel.score + 50);
    }
}

void Controller::checkTarget(){
    if (m_robotModel.robotPosition == m_mazeModel.targetPosition) {
        emit scoreChanged(m_robotModel.score + 100);
        emit levelDone();
    }
}


int Controller::getPercentEnergy() const{
    return (((m_mazeModel.maxEnergy - m_robotModel.steps) * 100) / m_mazeModel.maxEnergy);
}


bool Controller::moveRobot(){
    QPoint tar_pos = m_robotModel.robotPosition;
    switch (m_robotModel.robotDestination) {
        case Robot::LEFT: {
            tar_pos.rx()-=1;
            if (checkWall(tar_pos)) {
                emit positionChanged(tar_pos);
                return true;
            }
            return false;
        }
        case Robot::RIGHT:{
            tar_pos.rx()+=1;
            if (checkWall(tar_pos)) {
                emit positionChanged(tar_pos);
                return true;
            }
            return false;
        }
        case Robot::UP:{
            tar_pos.ry()-=1;
            if (checkWall(tar_pos)) {
                emit positionChanged(tar_pos);
                return true;
            }
            return false;
        }
        case Robot::DOWN:{
            tar_pos.ry()+=1;
            if (checkWall(tar_pos)) {
                emit positionChanged(tar_pos);
                return true;
            }
            return false;
        }
        default: return false;
    }
}

bool Controller::checkWall(QPoint dest){
    return !m_mazeModel.walls.contains(dest);
}

void Controller::doStep(int eventKey){
    emit stepsChanged(m_robotModel.steps + 1);
    updateScore(eventKey);
    checkEnergy();
}

void Controller::updateScore(int eventKey)
{
    if ((m_robotModel.steps <= m_mazeModel.maxEnergy) && m_robotModel.scoreIncrease)
            emit scoreChanged(m_robotModel.score + 1);
    else if (m_robotModel.score && eventKey == Qt::Key_Space) {
        emit scoreChanged(m_robotModel.score - 1);
    }
}

void Controller::checkEnergy()
{
    int curEnergy = getPercentEnergy();
    if (curEnergy <= 70) {
        if(m_robotModel.curColor == Robot::GREEN){
            emit curColorChanged(Robot::YELLOW);
            locateBattery();
        }
        else if(m_robotModel.tmpColor == Robot::GREEN){
            emit tmpColorChanged(Robot::YELLOW);
            locateBattery();
        }
    }
    if(curEnergy <= 30) {
        if(m_robotModel.curColor == Robot::YELLOW){
            emit curColorChanged(Robot::RED);
            locateBattery();
        }
        else if(m_robotModel.tmpColor == Robot::YELLOW){
            emit tmpColorChanged(Robot::RED);
            locateBattery();
        }
    }
    if(m_robotModel.steps == m_mazeModel.maxEnergy){
        emit curColorChanged(Robot::WHITE);
        emit tmpColorChanged(Robot::WHITE);
        emit scoreChanged(0);
        emit levelLost();
    }
}

void Controller::locateBattery(){
    QPoint battery;
    do{
        battery = getRandDot();
    } while ((m_robotModel.robotPosition == battery) || (m_mazeModel.targetPosition == battery)
             || (abs(battery.x() - m_robotModel.robotPosition.x()) > m_mazeModel.fieldWidth / 4)
             || (abs(battery.y() - m_robotModel.robotPosition.y()) > m_mazeModel.fieldHeight / 2));
    emit batteryLocated(battery);
}

QPoint Controller::getRandDot() {
    QTime time = QTime::currentTime();
    srand((uint) time.msec());
    QPoint dot;
    do{
        dot.rx() = rand() % m_mazeModel.fieldWidth;
        dot.ry() = rand() % m_mazeModel.fieldHeight;
    }while(m_mazeModel.walls.contains(dot));
    return dot;
}

void Controller::updateRobotModel(Robot::Model model) {
    m_robotModel = model;
    emit energyChanged(getPercentEnergy());
}

void Controller::updateMazeModel(Maze::Model model) {
    m_mazeModel = model;
}

void Controller::endGame() {
    QCoreApplication::quit();
}

void Controller::startGame() {
    emit resetMaze();
    emit resetRobot();
}

Controller::~Controller()=default;

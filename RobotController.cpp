
#include "RobotController.h"

#include <QTime>

RobotController::RobotController(const Robot::Model &robotModel, const Maze::Model &mazeModel, QObject *parent) :
m_robotModel(&robotModel), m_mazeModel(&mazeModel), QObject(parent)
{
    if(!m_states.isEmpty()) { m_states.clear();}
    m_states.push(State(m_robotModel->robotPosition,
                        m_mazeModel->batteries,
                        m_robotModel->score,
                        m_robotModel->energy,
                        m_robotModel->steps,
                        m_robotModel->robotDestination,
                        m_robotModel->curColor,
                        m_robotModel->tmpColor));
    m_animationTimerId = startTimer(ANIMATION_DELAY);
}

void RobotController::timerEvent(QTimerEvent *event) {
    if(event->timerId()==m_animationTimerId){
        emit skinAnimated();
    }
}

void RobotController::keyEventAction(QKeyEvent event) {
    switch (event.key()) {
        case Qt::Key_Left: {
            if(m_robotModel->robotDestination!=Robot::Directions::LEFT){
                emit destinationChanged(Robot::Directions::LEFT);
                doStep();
            }
            break;
        }
        case Qt::Key_Right:{
            if(m_robotModel->robotDestination!=Robot::Directions::RIGHT){
                emit destinationChanged(Robot::Directions::RIGHT);
                doStep();
            }
            break;
        }
        case Qt::Key_Up:{
            if(m_robotModel->robotDestination!=Robot::Directions::UP){
                emit destinationChanged(Robot::Directions::UP);
                doStep();
            }
            break;
        }
        case Qt::Key_Down:{
            if(m_robotModel->robotDestination!=Robot::Directions::DOWN){
                emit destinationChanged(Robot::Directions::DOWN);
                doStep();
            }
            break;
        }
        case Qt::Key_Space:{
            if(moveRobot()){
                checkTarget();
                checkBattery();
                doStep(&event);
            }
            break;
        }
        case Qt::Key_Backspace:{
            stepBack();
        }
        default:break;
    }

}


void RobotController::stepBack(){
    if(!m_states.isEmpty()){
        State lastState = m_states.pop();
        if(lastState.robotState.steps==m_robotModel->steps){
            stepBack();
        }
        else {
            emit robotStateChanged(lastState.robotState);
            emit mazeStateChanged(lastState.mazeState);
        }
        if(m_states.isEmpty()){
            m_states.push(State(m_robotModel->robotPosition,
                                m_mazeModel->batteries,
                                m_robotModel->score,
                                m_robotModel->energy,
                                m_robotModel->steps,
                                m_robotModel->robotDestination,
                                m_robotModel->curColor,
                                m_robotModel->tmpColor));
        }
    }
}

void RobotController::checkBattery()
{
    if (m_mazeModel->batteries.contains(m_robotModel->robotPosition)) {
        emit scoreIncreaseChanged(false);
        emit robotEnergyChanged(m_robotModel->trueWaySteps);
        emit curColorChanged(Robot::GREEN);
        emit tmpColorChanged(Robot::WHITE);
        emit batteryFinded(m_robotModel->robotPosition);
        emit robotScoreChanged(m_robotModel->score + 50);
    }
}
void RobotController::checkTarget()
{
    if (m_robotModel->robotPosition == m_mazeModel->targetPosition) {
        emit inGameChanged(false);
    }
}
int RobotController::getPercentEnergy() const
{
    return m_robotModel->energy * 100 / m_robotModel->trueWaySteps;
}
bool RobotController::moveRobot(){
    QPoint tar_pos = m_robotModel->robotPosition;
    switch (m_robotModel->robotDestination) {
        case Robot::LEFT: {
            tar_pos.rx()-=1;
            if (checkWall(tar_pos)) {
                emit robotPositionChanged(tar_pos);
                return true;
            }
            return false;
        }
        case Robot::RIGHT:{
            tar_pos.rx()+=1;
            if (checkWall(tar_pos)) {
                emit robotPositionChanged(tar_pos);
                return true;
            }
            return false;
        }
        case Robot::UP:{
            tar_pos.ry()-=1;
            if (checkWall(tar_pos)) {
                emit robotPositionChanged(tar_pos);
                return true;
            }
            return false;
        }
        case Robot::DOWN:{
            tar_pos.ry()+=1;
            if (checkWall(tar_pos)) {
                emit robotPositionChanged(tar_pos);
                return true;
            }
            return false;
        }
        default: return false;
    }
}

bool RobotController::checkWall(QPoint dest){
    return !m_mazeModel->walls.contains(dest);
}

void RobotController::doStep(QKeyEvent *event){
    if(m_robotModel->energy){emit robotEnergyChanged(m_robotModel->energy-1);}
    emit robotStepsChanged(m_robotModel->steps + 1);
    updateScore(event);
    checkEnergy();
    m_states.push(State(m_robotModel->robotPosition,
                        m_mazeModel->batteries,
                        m_robotModel->score,
                        m_robotModel->energy,
                        m_robotModel->steps,
                        m_robotModel->robotDestination,
                        m_robotModel->curColor,
                        m_robotModel->tmpColor));
}

void RobotController::updateScore(QKeyEvent *event)
{
    if ((m_robotModel->steps <= m_robotModel->trueWaySteps) && m_robotModel->scoreIncrease){
        emit robotScoreChanged(m_robotModel->score+1);
    } else if (m_robotModel->score && event != nullptr) {
        emit robotScoreChanged(m_robotModel->score-1);
    }
}

void RobotController::checkEnergy()
{
    int curEnergy = getPercentEnergy();
    if (curEnergy <= 70) {
        if(m_robotModel->curColor == Robot::GREEN){
            emit curColorChanged(Robot::YELLOW);
            locateBattery();
        }
        else if(m_robotModel->tmpColor == Robot::GREEN){
            emit tmpColorChanged(Robot::YELLOW);
            locateBattery();
        }
    }
    if(curEnergy <= 30) {
        if(m_robotModel->curColor == Robot::YELLOW){
            emit curColorChanged(Robot::RED);
            locateBattery();
        }
        else if(m_robotModel->tmpColor == Robot::YELLOW){
            emit tmpColorChanged(Robot::RED);
            locateBattery();
        }
    }
    if(m_robotModel->energy==0){
        emit curColorChanged(Robot::WHITE);
        emit tmpColorChanged(Robot::WHITE);
        emit inGameChanged(false);
    }
}

void RobotController::locateBattery(){
    QPoint battery;
    do{
        battery = getRandDot();
    } while ((m_robotModel->robotPosition == battery) || (m_mazeModel->targetPosition == battery)
             || (abs(battery.x() - m_robotModel->robotPosition.x()) > m_mazeModel->fieldWidth / 4)
             || (abs(battery.y() - m_robotModel->robotPosition.y()) > m_mazeModel->fieldHeight / 2));
    emit batteryLocated(battery);
}

QPoint RobotController::getRandDot() {
    QTime time = QTime::currentTime();
    srand((uint) time.msec());
    QPoint dot;
    do{
        dot.rx() = rand() % m_mazeModel->fieldWidth;
        dot.ry() = rand() % m_mazeModel->fieldHeight;
    }while(m_mazeModel->walls.contains(dot));
    return dot;
}

RobotController::~RobotController()=default;

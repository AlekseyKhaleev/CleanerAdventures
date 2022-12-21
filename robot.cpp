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




Robot::Robot():
Maze(),
m_targetImage(new  QImage(":/images/target.png")),
m_batteryImage(new QImage(":/images/battery.png")),
m_white(QVector<QImage*>{
        new QImage(":/images/VC_wt_lt"),
        new QImage(":/images/VC_wt_rt"),
        new QImage(":/images/VC_wt_up"),
        new QImage(":/images/VC_wt_dn")
}),
m_green(QVector<QImage*>{
        new QImage(":/images/VC_gr_lt"),
        new QImage(":/images/VC_gr_rt"),
        new QImage(":/images/VC_gr_up"),
        new QImage(":/images/VC_gr_dn")
}),
m_yellow(QVector<QImage*>{
        new QImage(":/images/VC_yw_lt"),
        new QImage(":/images/VC_yw_rt"),
        new QImage(":/images/VC_yw_up"),
        new QImage(":/images/VC_yw_dn")
}),
m_red(QVector<QImage*>{
        new QImage(":/images/VC_rd_lt"),
        new QImage(":/images/VC_rd_rt"),
        new QImage(":/images/VC_rd_up"),
        new QImage(":/images/VC_rd_dn")
})
{
    initRobot();
}

Robot::~Robot() = default;

void Robot::initRobot(){
    m_inGame = true;
    m_scoreIncrease = true;
    locateSelf();
    locateTarget();
    findTrueWay();
    m_curColor = green;
    m_tmpColor = white;
    if (!m_batteries.empty()) {
        m_batteries.clear();
    }
    m_batteries.push_back(QPoint{-1, -1});
    m_steps = 0;
    m_energy = m_trueWaySteps;
    if(!m_states.isEmpty()) { m_states.clear();}
    m_states.push(State(m_robotPosition,
                        m_batteries,
                        m_score,
                        m_energy,
                        m_steps,
                        m_robotDestination,
                        m_curColor,
                        m_tmpColor));
    m_animationTimerId = startTimer(ANIMATION_DELAY);
    m_repaintTimerId = startTimer(0);
}

void Robot::timerEvent(QTimerEvent *event){
    if(event->timerId() == m_repaintTimerId){
        emit scoreChanged(m_score);
        emit levelChanged(m_level);
        emit energyChanged(getPercentEnergy());
        repaint();
    } else if (event->timerId() == m_animationTimerId) {
        qSwap(m_curColor, m_tmpColor);
    }
}

void Robot::keyPressEvent(QKeyEvent *event){
    switch (event->key()) {
    case Qt::Key_Left: {
        if(m_robotDestination!=Directions::left){
            m_robotDestination = Directions::left;
            doStep();
        }
        break;
    }
    case Qt::Key_Right:{
        if(m_robotDestination!=Directions::right){
            m_robotDestination = Directions::right;
            doStep();
        }
        break;
    }
    case Qt::Key_Up:{
        if(m_robotDestination!=Directions::up){
            m_robotDestination = Directions::up;
            doStep();
        }
        break;
    }
    case Qt::Key_Down:{
        if(m_robotDestination!=Directions::down){
            m_robotDestination = Directions::down;
            doStep();
        }
        break;
    }
    case Qt::Key_Space:{
        if(moveRobot()){
            checkTarget();            
            checkBattery();
            doStep(event);
        }
        break;
    }
    case Qt::Key_Backspace:{
            stepBack();
        }
    default:break;
    }
}

void Robot::paintEvent(QPaintEvent *event){
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);

    if(m_inGame){
        drawMaze();
        drawRobot();
        drawTarget();
        drawBattery();

    }
    else if(m_energy != 0){
        levelDone();
    }
    else{
        gameOver();
    }
}

/******************** Getters  *************/
int Robot::getPercentEnergy() const
{
    return m_energy * 100 / m_trueWaySteps;
}
/*************************************************************/


void Robot::locateSelf(){
    QVector<QPoint> angles{
        QPoint{1,1},
        QPoint{1, FIELD_HEIGHT-2},
        QPoint{FIELD_WIDTH-2, 1},
        QPoint{FIELD_WIDTH-2,FIELD_HEIGHT-2}
    };
    m_robotPosition = angles[rand() % angles.size()];
    m_robotDestination = Directions::up;
}

void Robot::locateTarget()
{
    m_targetPosition = m_robotPosition;
    if (m_targetPosition.x() == 1) {
        m_targetPosition.rx() = FIELD_WIDTH - 2;
    } else {
        m_targetPosition.rx() = 1;
    }
    if (m_targetPosition.y() == 1) {
        m_targetPosition.ry() = FIELD_HEIGHT - 2;
    } else {
        m_targetPosition.ry() = 1;
    }
}

void Robot::locateBattery(){
    QPoint battery;
    do{
        battery = getRandDot();
    } while ((m_robotPosition == battery) || (m_targetPosition == battery)
             || (abs(battery.x() - m_robotPosition.x()) > FIELD_WIDTH / 4)
             || (abs(battery.y() - m_robotPosition.y()) > FIELD_HEIGHT / 2));
    m_batteries.push_back(battery);
}

void Robot::drawMaze(){
    QPainter qp(this);
    for(auto &w:qAsConst(m_walls)){
        qp.setBrush(Qt::black);
        qp.drawRect(w.x()*DOT_WIDTH, w.y()*DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT);
    }
}

void Robot::drawRobot(){
    QPainter qp(this);
    qp.drawImage(QRect(m_robotPosition.x() * DOT_WIDTH,
                       m_robotPosition.y() * DOT_HEIGHT,
                       DOT_WIDTH,
                       DOT_HEIGHT),
                 *m_robotSkin[m_curColor][m_robotDestination]);
}

void Robot::drawTarget()
{
    QPainter qp(this);
    qp.drawImage(QRect(m_targetPosition.x() * DOT_WIDTH,
                       m_targetPosition.y() * DOT_HEIGHT,
                       DOT_WIDTH,
                       DOT_HEIGHT),
                 *m_targetImage);
}

void Robot::drawBattery(){
    QPainter qp(this);
    for (auto &b : m_batteries) {
        if (b.x() >= 0) {
            qp.drawImage(QRect(b.x() * DOT_WIDTH, b.y() * DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT),
                         *m_batteryImage);
        }
    }
 }

bool Robot::moveRobot(){
    QPoint tar_pos = m_robotPosition;
    switch (m_robotDestination) {
    case left: {
        tar_pos.rx()-=1;
        if (checkWall(tar_pos)) {
            m_robotPosition = tar_pos;
            return true;
        }
        return false;
     }
     case right:{
        tar_pos.rx()+=1;
        if (checkWall(tar_pos)) {
            m_robotPosition = tar_pos;
            return true;
        }
        return false;
     }
     case up:{
        tar_pos.ry()-=1;
        if (checkWall(tar_pos)) {
            m_robotPosition = tar_pos;
            return true;
        }
        return false;
     }
     case down:{
        tar_pos.ry()+=1;
        if (checkWall(tar_pos)) {
            m_robotPosition = tar_pos;
            return true;
        }
        return false;
     }
     default: return false;
     }
 }

bool Robot::checkWall(QPoint dest){
     return !m_walls.contains(dest);
}

void Robot::checkTarget()
{
     if (m_robotPosition == m_targetPosition) {
        m_inGame = false;
     }
}

void Robot::checkBattery()
{
     if (m_batteries.contains(m_robotPosition)) {
        m_scoreIncrease = false;
        m_energy = m_trueWaySteps;
        m_curColor = green;
        m_tmpColor = white;
        m_batteries.removeAll(m_robotPosition);
        m_score += 50;
     }
}

void Robot::checkEnergy()
{
     int curEnergy = getPercentEnergy();
     emit energyChanged(curEnergy);
     if (curEnergy <= 70) {
        if(m_curColor == green){
            m_curColor = yellow;
            locateBattery();
        }
        else if(m_tmpColor == green){
            m_tmpColor = yellow;
            locateBattery();
        }
     }
    if(curEnergy <= 30) {
        if(m_curColor == yellow){
            m_curColor = red;
            locateBattery();
        }
        else if(m_tmpColor == yellow){
            m_tmpColor = red;
            locateBattery();
        }
    }
    if(m_energy==0){
        m_curColor = white;
        m_tmpColor = white;
        m_inGame = false;
    }
}

void Robot::levelDone(){
    killTimer(m_repaintTimerId);
    killTimer(m_animationTimerId);
    QMessageBox msgb;
    msgb.setText("<p align='center'>Level done, great! </p>");
    msgb.setInformativeText("<p align='center'>Wanna go next?</p>");
    msgb.setStandardButtons(QMessageBox::Close | QMessageBox::Retry);
    msgb.setDefaultButton(QMessageBox::Retry);
    int ret = msgb.exec();
    if (ret == QMessageBox::Retry) {
        initMaze();
        initRobot();
        m_level++;
        m_score += 100;
    } else {
        QCoreApplication::quit();
    }
}

void Robot::gameOver(){

    QMessageBox msgb;
    msgb.setText("<p align='center'>Ohh no! You lose! </p>");
    msgb.setInformativeText("<p align='center'>Wanna try again?</p>");
    msgb.setStandardButtons(QMessageBox::Close | QMessageBox::Retry);
    msgb.setDefaultButton(QMessageBox::Retry);
    int ret = msgb.exec();
    if (ret == QMessageBox::Retry){
        initMaze();
        initRobot();
        m_score = 0;
        m_level = 1;
    }
    else {
        killTimer(m_repaintTimerId);
        killTimer(m_animationTimerId);
        QCoreApplication::quit();
    }
}

void Robot::updateScore(QKeyEvent *keyEvent)
{
    m_steps++;
    if ((m_steps <= m_trueWaySteps) && m_scoreIncrease) {
        m_score++;
    } else if (m_score && keyEvent != nullptr) {
        m_score--;
    }
}

void Robot::doStep(QKeyEvent *event){
    if(m_energy){m_energy--;}
    updateScore(event);
    checkEnergy();
    m_states.push(State(m_robotPosition,
                        m_batteries,
                        m_score,
                        m_energy,
                        m_steps,
                        m_robotDestination,
                        m_curColor,
                        m_tmpColor));
}

void Robot::findTrueWay(){
    m_trueWaySteps = 2;
    QSet<QPoint> cells;
    for (auto k: qAsConst(m_cells)){
        cells.insert(k);
    }
    QPoint current = m_robotPosition;
    QVector<QPoint> neighbours;
    QStack<QPoint> way;
    cells.remove(current);
    while (current != m_targetPosition) {
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
    m_trueWaySteps += way.size();
    for(int i=1;i<way.size()-1;i++){
        if((way[i-1].x()==way[i].x()&&way[i+1].y()==way[i].y())||(way[i-1].y()==way[i].y()&&way[i+1].x()==way[i].x())){
            m_trueWaySteps++;
        }
    }    
 }

void Robot::stepBack(){
    if(!m_states.isEmpty()){
        State lastState = m_states.pop();
        if(lastState.STEPS==m_steps){
            stepBack();
        }
        else {
            setState(lastState);
        }
        if(m_states.isEmpty()){
            m_states.push(State(m_robotPosition,
                                m_batteries,
                                m_score,
                                m_energy,
                                m_steps,
                                m_robotDestination,
                                m_curColor,
                                m_tmpColor));
        }
    }
}

void Robot::setState(const State& curState){
    m_robotPosition = curState.POSITION;
    m_batteries = curState.BATTERIES;
    m_score = curState.SCORE;
    m_energy = curState.ENERGY;
    m_steps = curState.STEPS;
    m_robotDestination = curState.DESTINATION;
    m_curColor = curState.CURRENT_COLOR;
    m_tmpColor = curState.TEMPORARY_COLOR;
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

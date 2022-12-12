/*********************************************************************************************************************
* Данный модуль содержит определения иерархии классов, предназначенных для работы с таблицей данных отдела кадров
* (приложение Lab5-2)
*********************************************************************************************************************/

/* Подключение модулей */


#include <QPainter>
#include <QKeyEvent>
#include <QPixmap>
#include <QVector>
#include <QSet>
#include <QtGui>
#include <QMessageBox>
#include "Robot.h"




Robot::Robot():Maze(){
    initRobot();
}

Robot::~Robot() = default;

void Robot::initRobot(){
    m_inGame = true;
    locateSelf();
    locateTarget();
    findTrueWay();
    m_curColor = green;
    m_tmpColor = white;
    m_robTimer = startTimer(T_DELAY);
    m_anim_timer = startTimer(A_DELAY);    
    if(!m_battery.empty()){m_battery.clear();}
    m_battery.push_back(QPoint{-1,-1});
    m_steps = 0;
    m_energy = m_trueWay;
    if(!m_states.isEmpty()) { m_states.clear();}
    m_states.push(State(m_pos, m_battery, m_score, m_energy, m_steps, m_dest, m_curColor, m_tmpColor));
}

void Robot::timerEvent(QTimerEvent *event){
    if(event->timerId() == m_robTimer){
        repaint();
    }
    else if(event->timerId() == m_anim_timer){qSwap(m_curColor, m_tmpColor);}
}

void Robot::keyPressEvent(QKeyEvent *event){
    switch (event->key()) {
    case Qt::Key_Left: {
        m_dest = Directions::left;
        doStep();
        break;
    }
    case Qt::Key_Right:{
        m_dest = Directions::right;
        doStep();
        break;
    }
    case Qt::Key_Up:{
        m_dest = Directions::up;
        doStep();
        break;
    }
    case Qt::Key_Down:{
        m_dest = Directions::down;
        doStep();
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
    Q_UNUSED(event);
    if(m_inGame){
        Maze::drawMaze();
        drawRobot();
        drawTarget();
        drawBattery();
    }
    else if(getEnergy() != 0){
        levelDone();
    }
    else{
        gameOver();
    }
}

/******************** Getters  *************/
int Robot::getEnergy()
{
    return m_energy*100/m_trueWay;
}

int Robot::getScore()
{
    return m_score;
}

int Robot::getStates(){
    return m_states.size();
}

int Robot::getSteps()
{
    return m_steps;
}

int Robot::getTrueWay()
{
    return m_trueWay;
}

/*************************************************************/


void Robot::locateSelf(){
    QVector<QPoint> angles{
        QPoint{1,1},
        QPoint{1, FIELD_HEIGHT-2},
        QPoint{FIELD_WIDTH-2, 1},
        QPoint{FIELD_WIDTH-2,FIELD_HEIGHT-2}
    };
    m_pos = angles[rand()%angles.size()];
    m_dest = Directions::up;
}

void Robot::locateTarget(){
    m_target = m_pos;
    if(m_target.x() == 1) {m_target.rx() = FIELD_WIDTH - 2;}
    else                  {m_target.rx() = 1;}
    if(m_target.y() == 1) {m_target.ry() = FIELD_HEIGHT - 2;}
    else                  {m_target.ry() = 1;}
}

void Robot::locateBattery(){
    QPoint battery;
    do{
        battery = getRandDot();
    }while(m_walls.contains(battery)||m_pos == battery||m_target == battery||
           (abs(battery.x()-m_pos.x())>FIELD_WIDTH/4)||(abs(battery.y()-m_pos.y())>FIELD_HEIGHT/2));
    m_battery.push_back(battery);
}

void Robot::drawRobot(){
    QPainter qp(this);
    qp.drawPixmap(m_pos.x()*DOT_WIDTH, m_pos.y()*DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT, m_scin[m_curColor][m_dest]);
//    for(auto w:qAsConst(m_way)){
//        qp.setBrush(Qt::red);
//        qp.drawRect(w.x()*DOT_WIDTH, w.y()*DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT);
//    }
}

void Robot::drawTarget() {
    QPainter qp(this);
    qp.drawPixmap(m_target.x()*DOT_WIDTH, m_target.y()*DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT, m_targetPM);
 }

void Robot::drawBattery(){
     QPainter qp(this);
     for(auto &b:m_battery){
        if(b.x() >= 0){
            qp.drawPixmap(b.x()*DOT_WIDTH, b.y()*DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT, m_batteryPM);
        }
     }
 }

bool Robot::moveRobot(){
     QPoint tar_pos = m_pos;
     switch(m_dest){
     case left: {
        tar_pos.rx()-=1;
        if(checkWall(tar_pos)){
            m_pos = tar_pos;
            return true;
        }
        return false;
     }
     case right:{
        tar_pos.rx()+=1;
        if(checkWall(tar_pos)){
            m_pos = tar_pos;
            return true;
        }
        return false;
     }
     case up:{
        tar_pos.ry()-=1;
        if(checkWall(tar_pos)){
            m_pos = tar_pos;
            return true;
        }
        return false;
     }
     case down:{
        tar_pos.ry()+=1;
        if(checkWall(tar_pos)){
            m_pos = tar_pos;
            return true;
        }
        return false;
     }
     default: return false;
     }
 }

bool Robot::checkWall(QPoint dest){
     return !(m_walls.contains(dest)||dest.x() >= FIELD_WIDTH||dest.x() < 0||dest.y() >= FIELD_HEIGHT||dest.y() < 0);
 }

void Robot::checkTarget(){
     if(m_pos == m_target) {m_inGame = false;}
 }

void Robot::checkBattery(){
    if(m_battery.contains(m_pos)) {
        m_energy = m_trueWay;
        m_curColor = green;
        m_tmpColor = white;
        m_battery.removeAll(m_pos);
        m_score += 50;

    }
 }

void Robot::checkEnergy(){
    int curEnergy = getEnergy();
    if(curEnergy <= 70) {
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
    if(curEnergy==0){
        m_curColor = white;
        m_tmpColor = white;
        m_inGame = false;
    }

 }

void Robot::levelDone(){
     QMessageBox msgb;
     msgb.setText("<p align='center'>Level done, great! </p>");
     msgb.setInformativeText("<p align='center'>Wanna go next?</p>");
     msgb.setStandardButtons(QMessageBox::Close | QMessageBox::Retry);
     msgb.setDefaultButton(QMessageBox::Retry);
     int ret = msgb.exec();
     if (ret == QMessageBox::Retry){
         initMaze();
         initRobot();
     }
     else {
         killTimer(m_robTimer);
         killTimer(m_anim_timer);
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
    }
else {
    killTimer(m_robTimer);
    killTimer(m_anim_timer);
    QCoreApplication::quit();
}
}

void Robot::updateScore(QKeyEvent *keyEvent){
     m_steps++;
     if(m_steps<m_trueWay){m_score++;}
     else if(m_score&& keyEvent != nullptr){m_score--;}
}

void Robot::doStep(QKeyEvent *event){
    if(m_energy){m_energy--;}
    updateScore(event);
    checkEnergy();
    m_states.push(State(m_pos, m_battery, m_score, m_energy, m_steps, m_dest, m_curColor, m_tmpColor));
}

void Robot::findTrueWay(){
    m_trueWay = 1;
    QSet<QPoint> cells;
    for (auto k: qAsConst(m_cells)){
        cells.insert(k);
    }
    QPoint current = m_pos;
    QVector<QPoint> neighbours;
    QStack<QPoint> way;
    cells.remove(current);
    while(current != m_target){
        neighbours = getNeighbours(current, cells);
        if(neighbours.size() != 0){
            way.push(current);
            current = neighbours[rand()%neighbours.size()];
            cells.remove(current);

        }
        else if(!way.isEmpty()){
            current = way.pop();
        }
        else{break;}
    }
    for (auto k: qAsConst(way)){
        m_way.push(k);
    }
    m_trueWay+=way.size();
    for(int i=1;i<way.size()-1;i++){
        if((way[i-1].x()==way[i].x()&&way[i+1].y()==way[i].y())||(way[i-1].y()==way[i].y()&&way[i+1].x()==way[i].x())){
            m_trueWay++;
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
            m_states.push(State(m_pos, m_battery, m_score, m_energy, m_steps, m_dest, m_curColor, m_tmpColor));
        }
    }
}

void Robot::setState(State curState){
    m_pos = curState.POSITION;
    m_battery = curState.BATTERY;
    m_score = curState.SCORE;
    m_energy = curState.ENERGY;
    m_steps = curState.STEPS;
    m_dest = curState.DESTINATION;
    m_curColor = curState.CURRENT_COLOR;
    m_tmpColor = curState.TEMPORARY_COLOR;
}

QVector<QPoint> Robot::getNeighbours(QPoint current, QSet<QPoint> cells){
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

//void Robot::SetState(bool (*state)()){
//    ActiveState = state;
//}

//void Robot::Update(){
//    if (ActiveState != nullptr) {
//        ActiveState();
//    }
//}


bool Robot::wait(){

    std::cout<<u8' ';
    //move_cursor(CS);
    //std::cout<<GetArrow();
    //move_coursor(title);
    //std::cout<<"Current position (x,y): << CS;
    return 1;
}

bool Robot::analyze()
{
    return 0;
}

bool Robot::turn()
{
    return 0;
}



bool Robot::exit()
{
    return 0;
}

bool Robot::g_left()
{
    return 0;
}

bool Robot::g_right()
{
    return 0;
}

//QPoint Robot::SigHandle(signal sig){
//    if (sig[1]) {
//        SetState(analyze);
//        Update();
//    }
//    return CS;
//}



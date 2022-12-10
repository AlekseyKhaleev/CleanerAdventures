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
    locateSelf();
    locateTarget();
    m_curColor = green;
    m_tmpColor = white;
    m_timer = startTimer(T_DELAY);
    m_anim_timer = startTimer(A_DELAY);
    m_energy = MAX_ENERGY%100;
    if(!m_battery.empty()){m_battery.clear();}
    m_battery.push_back(QPoint{-1,-1});
    m_steps = 0;
    findShortWay();
}


void Robot::keyPressEvent(QKeyEvent *event){
    switch (event->key()) {
    case Qt::Key_Left: {
        m_dest = Directions::left;
        m_energy--;
        checkEnergy();
        break;
    }
    case Qt::Key_Right:{
        m_dest = Directions::right;
        m_energy--;
        checkEnergy();
        updateScore();
        break;
    }
    case Qt::Key_Up:{
        m_dest = Directions::up;
        m_energy--;
        checkEnergy();
        break;
    }
    case Qt::Key_Down:{
        m_dest = Directions::down;
        m_energy--;
        checkEnergy();
        break;
    }
    case Qt::Key_Space:{
        if(moveRobot()){
            checkTarget();
            m_energy--;
            checkBattery();
            checkEnergy();
        }
        break;
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
    else{
        gameOver();
    }
}

void Robot::timerEvent(QTimerEvent *event){
    if(event->timerId() == m_timer){
        repaint();
    }
    else if(event->timerId() == m_anim_timer){qSwap(m_curColor, m_tmpColor);}
}

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
    }while(m_walls.contains(battery)||m_pos == battery||m_target == battery);
    m_battery.push_back(battery);
}

void Robot::drawRobot(){
    QPainter qp(this);
    qp.drawPixmap(m_pos.x()*DOT_WIDTH, m_pos.y()*DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT, m_scin[m_curColor][m_dest]);
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
        m_energy = MAX_ENERGY;
        m_curColor = green;
        m_tmpColor = white;
        m_battery.removeAll(m_pos);

    }
 }

 void Robot::checkEnergy(){
    if(m_energy>0){
        if(m_energy>30&&m_energy<=50&&(m_curColor==green||m_tmpColor==green)){
            m_curColor = yellow;
            locateBattery();
        }else if((m_curColor == yellow||m_tmpColor==yellow)&&m_energy<30){
            m_curColor = red;
            locateBattery();
        }
    }
 }



 void Robot::gameOver(){
//     QRect rect = frameGeometry();
//     rect.moveCenter(QGuiApplication::primaryScreen()->availableGeometry().center());
     QMessageBox msgb;
//     msgb.setGeometry(rect);
     msgb.setText("<p align='center'>Game Over</p>");
     msgb.setInformativeText("<p align='center'>Try again?</p>");
     msgb.setStandardButtons(QMessageBox::Close | QMessageBox::Retry);
     msgb.setDefaultButton(QMessageBox::Retry);
     int ret = msgb.exec();
     if (ret == QMessageBox::Retry){
         initMaze();
         initRobot();
     }
     else {
         killTimer(m_timer);
         killTimer(m_anim_timer);
         QCoreApplication::quit();
     }
 }

 void Robot::updateScore(){
     m_steps++;
     if(m_steps<m_shortWay){m_score++;}
     else {m_score--;}
 }

 void Robot::findShortWay(){

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



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
    m_animation = startTimer(A_DELAY);
    m_energy = MAX_ENERGY;
}


void Robot::keyPressEvent(QKeyEvent *event){
    switch (event->key()) {
    case Qt::Key_Left: {
        m_dest = Directions::left;
        m_energy--;
        break;
    }
    case Qt::Key_Right:{
        m_dest = Directions::right;
        m_energy--;
        break;
    }
    case Qt::Key_Up:{
        m_dest = Directions::up;
        m_energy--;
        break;
    }
    case Qt::Key_Down:{
        m_dest = Directions::down;
        m_energy--;
        break;
    }
    case Qt::Key_Space:{
        moveRobot();
        checkTarget();
        m_energy--;
        checkBattery();
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
    }
    else{
        gameOver();
    }
}

void Robot::timerEvent(QTimerEvent *event){
    if(event->timerId() == m_timer){
        setColor();
        repaint();
    }
    else if(event->timerId() == m_animation){qSwap(m_curColor, m_tmpColor);}

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

void Robot::locateBattery()
{
    do{
        m_battery = getRandDot();
    }while(m_walls.contains(m_battery)||m_pos == m_battery||m_target == m_battery);
}

void Robot::drawRobot(){
    QPainter qp(this);
    qp.drawPixmap(m_pos.x()*DOT_WIDTH, m_pos.y()*DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT, m_scin[m_curColor][m_dest]);
}
 void Robot::drawTarget() {
    QPainter qp(this);
    qp.setBrush(Qt::red);
    qp.drawEllipse(m_target.x()*DOT_WIDTH, m_target.y()*DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT);
 }

 void Robot::moveRobot(){
     QPoint tar_pos = m_pos;
     switch(m_dest){
     case left: {
        tar_pos.rx()-=1;
        if(checkWall(tar_pos)){m_pos = tar_pos;}
        break;
     }
     case right:{
        tar_pos.rx()+=1;
        if(checkWall(tar_pos)){m_pos = tar_pos;}
        break;
     }
     case up:{
        tar_pos.ry()-=1;
        if(checkWall(tar_pos)){m_pos = tar_pos;}
        break;
     }
     case down:{
        tar_pos.ry()+=1;
        if(checkWall(tar_pos)){m_pos = tar_pos;}
        break;
     }
     default: break;
     }
 }

 bool Robot::checkWall(QPoint dest){
     return !(m_walls.contains(dest)||dest.x() >= FIELD_WIDTH||dest.x() < 0||dest.y() >= FIELD_HEIGHT||dest.y() < 0);
 }

 void Robot::checkTarget(){
     if(m_pos == m_target) {m_inGame = false;}
 }

 void Robot::checkBattery()
 {
    if(m_pos == m_battery) {
        m_energy = MAX_ENERGY;
        m_battery = QPoint{-1,-1};
    }
 }

 void Robot::setColor()
 {
    int proc_energy = m_energy%100;
    if(proc_energy>1){
        if(proc_energy>30){
            if(proc_energy>50){
                m_curColor = green;
            }
            m_curColor = yellow;
        }
        m_curColor = green;
    }
 }

 void Robot::gameOver(){
     QRect rect = frameGeometry();
     rect.moveCenter(QGuiApplication::primaryScreen()->availableGeometry().center());
     QMessageBox msgb;
     msgb.setGeometry(rect);
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
         killTimer(m_animation);
         QCoreApplication::quit();
     }
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



/*********************************************************************************************************************
* Данный модуль содержит определения иерархии классов, предназначенных для работы с таблицей данных отдела кадров
* (приложение Lab5-2)
*********************************************************************************************************************/

/* Подключение модулей */

#include <string>
#include <iostream>
#include <vector>
#include <cstring>
#include <QPainter>
#include "Robot.h"
#include <QKeyEvent>
#include <QPixmap>




Robot::Robot():Map(){
    initRobot();
}

void Robot::doPainting()
{
    QPainter qp(this);
    if (m_inGame){
        qp.drawPixmap(m_pos.x()*DOT_WIDTH, m_pos.y()*DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT, DirIcons[m_dest]);
//        qp.setBrush(Qt::green);
//        qp.drawEllipse(m_pos.x()*DOT_WIDTH, m_pos.y()*DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT);
    }
    else
        gameOver();

}


Robot::~Robot() = default;

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

void Robot::locateSelf()
{
//    do{
//        m_pos = getRandDot();
//    }while(m_walls.contains(m_pos)||m_target == m_pos);
    QVector<QPoint> angles{
        QPoint{1,1},
        QPoint{1, FIELD_HEIGHT-2},
        QPoint{FIELD_WIDTH-2, 1},
        QPoint{FIELD_WIDTH-2,FIELD_HEIGHT-2}
    };
    m_pos = angles[rand()%angles.size()];
    m_target = m_pos;
    if(m_target.x() == 1){m_target.rx() = FIELD_WIDTH - 2;}
    else{m_target.rx() = 1;}
    if(m_target.y() == 1){m_target.ry() = FIELD_HEIGHT - 2;}
    else{m_target.ry() = 1;}
    m_dest = Directions::up;
}

void Robot::initRobot()
{
    locateSelf();
}

void Robot::moveRobot()
{
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

bool Robot::checkWall(QPoint dest)
{
//    bool result = true;
    return !(m_walls.contains(dest)||dest.x() >= FIELD_WIDTH||dest.x() < 0||dest.y() >= FIELD_HEIGHT||dest.y() < 0);
//    if(dest.x() >= FIELD_WIDTH) {result=false;}
//    if(dest.x() < 0)            {result=false;}
//    if(dest.y() >= FIELD_HEIGHT){result=false;}
//    if(dest.y() < 0)            {result=false;}
//    return result;
}

void Robot::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    if(key == Qt::Key_Left ){m_dest = Directions::left; }
    if(key == Qt::Key_Right){m_dest = Directions::right;}
    if(key == Qt::Key_Up )  {m_dest = Directions::up;   }
    if(key == Qt::Key_Down ){m_dest = Directions::down; }
    if(key == Qt::Key_Space){moveRobot();}
    repaint();
}

void Robot::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    Map::drawMap();
    doPainting();
}

void Robot::timerEvent(QTimerEvent *event){
    Q_UNUSED(event);

    if(m_inGame){

       // Update();
//        check_apple();
        //move();
//        check_field();
    }
    this->repaint();
}

//QPoint Robot::SigHandle(signal sig){
//    if (sig[1]) {
//        SetState(analyze);
//        Update();
//    }
//    return CS;
//}



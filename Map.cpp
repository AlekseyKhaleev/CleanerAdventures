#include "Map.h"
#include <QKeyEvent>
#include <QPainter>
#include <qrandom.h>
#include <QTime>
#include <QMessageBox>
#include <QPushButton>
#include <QDebug>
#include <QCoreApplication>
#include <QStyle>
#include <QtWidgets>
#include <QtGui>

void Map::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    doDrawing();
}

Map::Map(){
    QRect rect = frameGeometry();
    rect.moveCenter(QGuiApplication::primaryScreen()->availableGeometry().center());
    this->setGeometry(rect);
    this->resize(DOT_WIDTH*FIELD_WIDTH, DOT_HEIGHT*FIELD_HEIGHT);
    this->setWindowTitle("Course work: FSM robot");


    initGame();
}

void Map::initGame(){
    m_inGame=true;
//    m_dots.resize(3);
//    m_dir = right;
//    for (int i=0; i<m_dots.size(); ++i){
//        m_dots[i].rx()= m_dots.size() - i-1;
//        m_dots[i].ry()=0;
//    }
    locateLines();
    locateWalls();
    locateTarget();
//    m_timerId = startTimer(DELAY);

}



void Map::doDrawing()
{
    QPainter qp(this);
    if (m_inGame){
        qp.setPen(Qt::black);
        for(int i=0; i<16;++i){qp.drawLines(m_lines);}

        for(auto &w:m_walls){
            qp.setBrush(Qt::black);
            qp.drawRect(w.x()*DOT_WIDTH, w.y()*DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT);
        }

        qp.setBrush(Qt::red);
        qp.drawEllipse(m_target.x()*DOT_WIDTH, m_target.y()*DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT);
//        for(int i=0; i<m_dots.size();++i){
//            if(i==0){
//                qp.setBrush(Qt::white);
//                qp.drawEllipse(m_dots[i].x()*DOT_WIDTH, m_dots[i].y()*DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT);

//            }else{
//                qp.setBrush(Qt::green);
//                qp.drawEllipse(m_dots[i].x()*DOT_WIDTH, m_dots[i].y()*DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT);

//            }
//        }

    }else{
        gameOver();
    }
}

QPoint Map::getRandDot()
{
    QTime time = QTime::currentTime();
    srand((uint) time.msec());
    QPoint dot;
    dot.rx() = rand() % DOT_WIDTH;
    dot.ry() = rand() % DOT_HEIGHT;
    return dot;
}

QPoint Map::locateTarget()
{
    do{
        m_target = getRandDot();
    }while(m_walls.contains(m_target));

    return m_target;
}

void Map::locateWalls()
{
    QPoint wall;
    for(int c=0;c<WALLS_COUNT;++c){
        wall = locateTarget();
        m_walls.push_back(wall);
        if(rand()%2){
            for(int i=0;i < rand()%WALL_MAX_LEN;++i){
                wall.rx()+=1;
                m_walls.push_back(wall);
            }
        }else{
            for(int i=0;i < rand()%WALL_MAX_LEN;++i){
                wall.ry()+=1;
                m_walls.push_back(wall);
            }
        }
    }

}

void Map::locateLines()
{
    for(int y=0;y<FIELD_HEIGHT*DOT_HEIGHT;y+=DOT_HEIGHT){
        m_lines.push_back(QPoint(0,y));
        m_lines.push_back(QPoint(FIELD_WIDTH*DOT_WIDTH,y));
    }
    for(int x=0;x<FIELD_WIDTH*DOT_WIDTH;x+=DOT_WIDTH){
        m_lines.push_back(QPoint(x,0));
        m_lines.push_back(QPoint(x,FIELD_HEIGHT*DOT_HEIGHT));
    }
}

void Map::gameOver()
{
    QRect rect = frameGeometry();
    rect.moveCenter(QGuiApplication::primaryScreen()->availableGeometry().center());
    QMessageBox msgb;
    msgb.setGeometry(rect);
    msgb.setText("<p align='center'>Game Over</p>");
    msgb.setInformativeText("<p align='center'>Try again?</p>");
    msgb.setStandardButtons(QMessageBox::Close | QMessageBox::Retry);
    msgb.setDefaultButton(QMessageBox::Retry);
    int ret = msgb.exec();
    if (ret == QMessageBox::Retry){initGame();}
    else {QCoreApplication::quit();}
 }

////void Map::move()
//{
//    for (int i=m_dots.size()-1;i>0;--i){
//        m_dots[i] = m_dots[i-1];
//    }

//    switch(m_dir){
//    case left:  {m_dots[0].rx()-= 1;break;}
//    case right: {m_dots[0].rx()+= 1;break;}
//    case up:    {m_dots[0].ry()-= 1;break;}
//    case down:  {m_dots[0].ry()+= 1;break;}
//    default:break;
//    }
//}

//void Map::check_field()
//{
//    if(m_dots.size()>4){
//        for(int i=1;i<m_dots.size();++i){
//            if(m_dots[0]==m_dots[i]){
//                m_inGame = false;
//            }
//        }
//    }
//    if(m_dots[0].x() >= FIELD_WIDTH) {m_inGame=false;}
//    if(m_dots[0].x() < 0)            {m_inGame=false;}
//    if(m_dots[0].y() >= FIELD_HEIGHT){m_inGame=false;}
//    if(m_dots[0].y() < 0)            {m_inGame=false;}

//    if(!m_inGame){
//        killTimer(m_timerId);
//    }
//}

//void Map::check_target()
//{
//    if (m_target == m_dots[0]){
//        m_dots.push_back(QPoint(0,0));
//        locateTarget();
//    }
//}

////void Game::timerEvent(QTimerEvent *event){
//    Q_UNUSED(event);

//    if(m_inGame){
//        check_apple();
//        move();
//        check_field();
//    }
//    this->repaint();
//}

//void Map::keyPressEvent(QKeyEvent *event){
//    int key = event->key();
//    if(key == Qt::Key_Left && m_dir != Directions::right){m_dir = Directions::left; }
//    if(key == Qt::Key_Right && m_dir != Directions::left){m_dir = Directions::right;}
//    if(key == Qt::Key_Up && m_dir != Directions::down)   {m_dir = Directions::up;   }
//    if(key == Qt::Key_Down && m_dir != Directions::up)   {m_dir = Directions::down; }

//}




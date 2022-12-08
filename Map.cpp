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



Map::Map(){
    QRect rect = frameGeometry();
    rect.moveCenter(QGuiApplication::primaryScreen()->availableGeometry().center());
    this->setGeometry(rect);
    this->resize(DOT_WIDTH*FIELD_WIDTH, DOT_HEIGHT*FIELD_HEIGHT);
    this->setWindowTitle("Course work: FSM robot");
    initGame();
}

void Map::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    drawMap();
}

void Map::initGame(){
    m_inGame=true;
    locateLines();
    locateWalls();
}

void Map::drawMap()
{
    QPainter qp(this);
    if (m_inGame){
//        qp.setPen(Qt::black);
//        for(int i=0; i<16;++i){qp.drawLines(m_lines);}

        for(auto w:qAsConst(m_walls)){
            qp.setBrush(Qt::black);
            qp.drawRect(w.x()*DOT_WIDTH, w.y()*DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT);
        }

        qp.setBrush(Qt::red);
        qp.drawEllipse(m_target.x()*DOT_WIDTH, m_target.y()*DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT);

//        qp.setBrush(Qt::green);
//        qp.drawEllipse(m_start.x()*DOT_WIDTH, m_start.y()*DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT);

    }else
    {
        gameOver();
    }
}

QPoint Map::getRandDot()
{
    QTime time = QTime::currentTime();
    srand((uint) time.msec());
    QPoint dot;
    dot.rx() = rand() % FIELD_WIDTH;
    dot.ry() = rand() % FIELD_HEIGHT;
    return dot;
}

void Map::locateStart()
{
    do{
        m_start = getRandDot();
    }while(m_walls.contains(m_start));
}

void Map::locateWalls()
{
    QPoint dot;
    for(int y=0;y<FIELD_HEIGHT;y++){
        for(int x=0;x<FIELD_WIDTH;x++){
            if((x%2 !=0 && y%2 !=0) &&
                    (y <FIELD_HEIGHT-1 &&x < FIELD_WIDTH-1)){
                dot.rx() = x;
                dot.ry()= y;
                m_cells.insert(dot);

            }
            else
            {
                dot.rx() = x;
                dot.ry()= y;
                m_walls.insert(dot);
            }
        }
    }


    locateStart();
    QPoint current = m_start;
    QPoint next;
    QVector<QPoint> neighbours;
    QStack<QPoint> way;
    do{
        neighbours = getNeighbours(current);
        if(neighbours.size() != 0){
            next = neighbours[rand()%neighbours.size()];
            way.push(current);
            QPoint toDel = current;
            if(current.y() == next.y()){
                toDel.rx() = current.x()+((next.x()-current.x())/std::abs(next.x()-current.x()));
            }else
            {
            toDel.ry() = current.y()+((next.y()-current.y())/std::abs(next.y()-current.y()));
            }
            m_walls.remove(toDel);
            current = next;
            m_cells.remove(current);
            m_steps ++;
        } else if(way.size()>0){
            current = way.pop();
        }
        else{
            QPoint key;
            for (auto k: qAsConst(m_cells)){
                key = k;
                break;
            }
            current = key;
        }
    }while(m_cells.size() > 0);
    m_target = current;
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

QVector<QPoint> Map::getNeighbours(QPoint current)
{
    QVector<QPoint> curNeighbours;
    current.rx()+=2;
    if(m_cells.contains(current)){
        curNeighbours.push_back(current);
    }
    current.rx()-=4;
    if(m_cells.contains(current)){
        curNeighbours.push_back(current);
    }
    current.rx()+=2;
    current.ry()+=2;
    if(m_cells.contains(current)){
        curNeighbours.push_back(current);
    }
    current.ry()-=4;
    if(m_cells.contains(current)){
        curNeighbours.push_back(current);
    }
    return curNeighbours;
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





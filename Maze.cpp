#include "Maze.h"
#include <QKeyEvent>
#include <QPainter>
#include <qrandom.h>
#include <QTime>
#include <QMessageBox>
#include <QStyle>
#include <QtGui>



Maze::Maze(){
    this->resize(DOT_WIDTH*FIELD_WIDTH, DOT_HEIGHT*FIELD_HEIGHT);
    this->setWindowTitle("Course work: FSM robot");
    initMaze();
}

void Maze::initMaze(){
//    if(!m_cells.isEmpty()){
//        m_cells.clear();
//    }
    locateWalls();
}

void Maze::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    drawMaze();
}

void Maze::drawMaze(){
    QPainter qp(this); 
    for(auto w:qAsConst(m_walls)){
        qp.setBrush(Qt::black);
        qp.drawRect(w.x()*DOT_WIDTH, w.y()*DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT);
    }
}

QPoint Maze::getRandDot(){
    QTime time = QTime::currentTime();
    srand((uint) time.msec());
    QPoint dot;
    dot.rx() = rand() % FIELD_WIDTH;
    dot.ry() = rand() % FIELD_HEIGHT;
    return dot;
}

void Maze::locateWalls(){
    QPoint dot;
    for(int y=0;y<FIELD_HEIGHT;y++){
        for(int x=0;x<FIELD_WIDTH;x++){
            if((x%2 !=0 && y%2 !=0) &&
                    (y <FIELD_HEIGHT-1 &&x < FIELD_WIDTH-1)){
                dot.rx() = x;
                dot.ry()= y;
                m_cells.insert(dot);

            }
            else{
                dot.rx() = x;
                dot.ry()= y;
                m_walls.insert(dot);
            }
        }
    }
    QSet<QPoint> cells;
    for (auto k: qAsConst(m_cells)){
        cells.insert(k);
    }
    QPoint current = getRandDot();
    QPoint next;
    QVector<QPoint> neighbours;
    QStack<QPoint> way;
    do{
        neighbours = getNeighbours(current, cells);
        if(neighbours.size() != 0){
            next = neighbours[rand()%neighbours.size()];
            way.push(current);
            QPoint toDel = current;
            if(current.y() == next.y()){
                toDel.rx() = current.x()+((next.x()-current.x())/std::abs(next.x()-current.x()));
            }else{
            toDel.ry() = current.y()+((next.y()-current.y())/std::abs(next.y()-current.y()));
            }
            m_walls.remove(toDel);
            m_cells.insert(toDel);
            current = next;
            cells.remove(current);
        } else if(way.size()>0){
            current = way.pop();
        }
        else{
            QPoint key;
            for (auto k: qAsConst(cells)){
                key = k;
                break;
            }
            current = key;
        }
    }while(cells.size() > 0);
}

QVector<QPoint> Maze::getNeighbours(QPoint current, QSet<QPoint> cells){
    QVector<QPoint> curNeighbours;
    current.rx()+=2;
    if(cells.contains(current)){
        curNeighbours.push_back(current);
    }
    current.rx()-=4;
    if(cells.contains(current)){
        curNeighbours.push_back(current);
    }
    current.rx()+=2;
    current.ry()+=2;
    if(cells.contains(current)){
        curNeighbours.push_back(current);
    }
    current.ry()-=4;
    if(cells.contains(current)){
        curNeighbours.push_back(current);
    }
    return curNeighbours;
}

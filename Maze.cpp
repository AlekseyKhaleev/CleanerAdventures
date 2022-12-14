#include "Maze.h"
#include <qrandom.h>
#include <QGuiApplication>
#include <QScreen>
#include <QTime>
#include <QStack>



Maze::Maze(){    
    initFieldSize();
    initMaze();
//    this->resize(DOT_WIDTH*FIELD_WIDTH, DOT_HEIGHT*FIELD_HEIGHT);
}

void Maze::initMaze(){    
    initDefaultMazeMap();
    locateWalls();
}

QPoint Maze::getRandDot(){
    QTime time = QTime::currentTime();
    srand((uint) time.msec());
    QPoint dot;
    do{
        dot.rx() = rand() % FIELD_WIDTH;
        dot.ry() = rand() % FIELD_HEIGHT;
    }while(m_walls.contains(dot));
    return dot;
}

void Maze::locateWalls(){
    QSet<QPoint> cells;
    for (auto &k: qAsConst(m_cells)){
        cells.insert(k);
    }
    QPoint current = getRandDot();
    QPoint next;
    QVector<QPoint> neighbours;
    QStack<QPoint> way;
    do{
        neighbours = getMazeNeighbours(current, cells);
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
            for (auto &k: qAsConst(cells)){
                key = k;
                break;
            }
            current = key;
        }
    }while(cells.size() > 0);
}

QVector<QPoint> Maze::getMazeNeighbours(QPoint current, QSet<QPoint> cells){
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

void Maze::initFieldSize(){
    auto const rec = QGuiApplication::primaryScreen()->size();
    FIELD_WIDTH = rec.width()/DOT_WIDTH;
//    FIELD_WIDTH = FIELD_WIDTH+(FIELD_WIDTH % 2)-1;
    FIELD_HEIGHT = rec.height()*0.8/DOT_HEIGHT;
//    FIELD_HEIGHT = FIELD_HEIGHT+(FIELD_HEIGHT % 2)-1;
}

void Maze::initDefaultMazeMap(){
    m_cells.clear();
    m_walls.clear();
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
}

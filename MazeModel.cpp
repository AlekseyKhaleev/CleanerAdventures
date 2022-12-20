#include "MazeModel.h"

#include <QGuiApplication>
#include <qpoint.h>
#include <qset.h>
#include <QStack>
#include <QTime>
#include <QVector>
#include <QWidget>

using namespace Maze;

//************************************************

//Constructor
MazeModel::MazeModel(QObject *parent):
QObject(parent),
m_mazeState(new Model)

{
    initFieldSize();
    initMaze();
}

//Destructor
MazeModel::~MazeModel() {
    delete m_mazeState;
}

//******************************************************

void MazeModel::initMaze(){
    initDefaultMazeMap();
    locateWalls();
    if (!m_mazeState->batteries.empty()) {
        m_mazeState->batteries.clear();
    }
    m_mazeState->batteries.push_back(QPoint{-1, -1});
    m_mazeState->targetPosition = QPoint(m_mazeState->fieldWidth-2,m_mazeState->fieldHeight-2);
    m_mazeState->level++;
    emit modelChanged(*m_mazeState);
}

QPoint MazeModel::getRandDot(){
    QTime time = QTime::currentTime();
    srand((uint) time.msec());
    QPoint dot;
    do{
        dot.rx() = rand() % m_mazeState->fieldWidth;
        dot.ry() = rand() % m_mazeState->fieldHeight;
    }while(m_mazeState->walls.contains(dot));
    return dot;
}

void MazeModel::locateWalls(){
    QSet<QPoint> cells;
    for (auto &k: qAsConst(m_mazeState->cells)){
        cells.insert(k);
    }
    QPoint current = getRandDot();
    QPoint next;
    QVector<QPoint> neighbours;
    QStack<QPoint> way;
    do{
        neighbours = getMazeNeighbours(current, cells);
        if(!neighbours.isEmpty()){
            next = neighbours[rand()%neighbours.size()];
            way.push(current);
            QPoint toDel = current;
            if(current.y() == next.y()){
                toDel.rx() = current.x()+((next.x()-current.x())/std::abs(next.x()-current.x()));
            }else{
            toDel.ry() = current.y()+((next.y()-current.y())/std::abs(next.y()-current.y()));
            }
            m_mazeState->walls.remove(toDel);
            m_mazeState->cells.insert(toDel);
            current = next;
            cells.remove(current);
        } else if(!way.empty()){
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
    }while(!cells.empty());
}

QVector<QPoint> MazeModel::getMazeNeighbours(QPoint current, const QSet<QPoint>& cells){
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

void MazeModel::initFieldSize(){
    auto const rec = QGuiApplication::primaryScreen()->size();
    m_mazeState->fieldWidth = rec.width()/Maze::Model::DOT_SIDE;
//    m_mazeState->fieldWidth = m_mazeState->fieldWidth+(m_mazeState->fieldWidth % 2)-1;
    m_mazeState->fieldHeight = rec.height()*0.8/Maze::Model::DOT_SIDE;
//    m_mazeState->fieldHeight = m_mazeState->fieldHeight+(m_mazeState->fieldHeight % 2)-1;
}

void MazeModel::initDefaultMazeMap(){
    m_mazeState->cells.clear();
    m_mazeState->walls.clear();
    QPoint dot;
    for(int y=0;y<m_mazeState->fieldHeight;y++){
        for(int x=0;x<m_mazeState->fieldWidth;x++){
            if ((x % 2 != 0 && y % 2 != 0) && (y < m_mazeState->fieldHeight - 1 && x < m_mazeState->fieldWidth - 1)) {
                dot.rx() = x;
                dot.ry()= y;
                m_mazeState->cells.insert(dot);
            } else {
                dot.rx() = x;
                dot.ry()= y;
                m_mazeState->walls.insert(dot);
            }
        }
    }
}

void MazeModel::addBattery(QPoint value) {
    m_mazeState->batteries.push_back(value);
    emit modelChanged(*m_mazeState);
}

void MazeModel::delBattery(QPoint value) {
    m_mazeState->batteries.removeAll(value);
    emit modelChanged(*m_mazeState);
}

Model& MazeModel::getMazeModel() const{
    return *m_mazeState;

}

void MazeModel::setMazeState(const Maze::Model &state) {
    m_mazeState->batteries = state.batteries;
    emit modelChanged(*m_mazeState);
}



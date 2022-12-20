#include "MazeView.h"

#include <QPainter>
#include <QKeyEvent>
#include <QVector>
#include <QSet>
#include <QtGui>
#include <QMessageBox>
#include "RobotModel.h"
#include <QStyleOption>

using namespace Maze;

MazeView::MazeView(const Model &targetModel, QWidget *parent):
QWidget(parent),
m_viewModel(targetModel),
m_targetImage(new  QImage(":/images/target.png")),
m_batteryImage(new QImage(":/images/battery.png"))
{
    repaint();
}

MazeView::~MazeView()=default;



void MazeView::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event)

    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    drawMaze();
    drawTarget();
    drawBattery();
}

void MazeView::drawMaze(){
    QPainter qp(this);
    for(auto &w:qAsConst(m_viewModel.walls)){
        qp.setBrush(Qt::black);
        qp.drawRect(w.x()*Maze::Model::DOT_SIDE, w.y()*Maze::Model::DOT_SIDE, Maze::Model::DOT_SIDE, Maze::Model::DOT_SIDE);
    }
}

void MazeView::drawTarget(){
    QPainter qp(this);
    qp.drawImage(QRect(m_viewModel.targetPosition.x() * Maze::Model::DOT_SIDE,
                       m_viewModel.targetPosition.y() * Maze::Model::DOT_SIDE,
                       Maze::Model::DOT_SIDE, Maze::Model::DOT_SIDE), *m_targetImage);
}

void MazeView::drawBattery(){
    QPainter qp(this);
    for (auto &b : m_viewModel.batteries) {
        if (b.x() >= 0) {
            qp.drawImage(QRect(b.x() * Maze::Model::DOT_SIDE, b.y() * Maze::Model::DOT_SIDE, Maze::Model::DOT_SIDE, Maze::Model::DOT_SIDE),
                         *m_batteryImage);
        }
    }
}

void MazeView::updateModel(Maze::Model model) {
    m_viewModel = model;
    repaint();
}





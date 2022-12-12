#include "energyWidget.h"
#include "Robot.h"
#include <QTimerEvent>
#include <QPainter>
#include <QTextItem>

EnergyWidget::EnergyWidget(Robot *object){
    m_statTimer = startTimer(30);
    m_robot = object;
    this->setMaximumWidth(m_robot->width()/3);



}

void EnergyWidget::timerEvent(QTimerEvent *event){
    if(event->timerId() == m_statTimer){
        setEnergyStatus();
        repaint();
    }
}

void EnergyWidget::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    drawStatus();
}

void EnergyWidget::setEnergyStatus(){
    int curEnergy = m_robot->getEnergy();
    if(curEnergy == 0)      {m_enStatus = en_0;}
    else if(curEnergy <= 10) {m_enStatus = en_10; }
    else if(curEnergy <= 30) {m_enStatus = en_30; }
    else if(curEnergy <= 50) {m_enStatus = en_50; }
    else if(curEnergy <= 70) {m_enStatus = en_70; }
    else if(curEnergy <= 80) {m_enStatus = en_80; }
    else                    {m_enStatus = en_90;  }
}

void EnergyWidget::drawStatus(){

    QPainter qp(this);
    qp.drawPixmap(0,0, m_enStatusPM[m_enStatus].width()*0.32, m_enStatusPM[m_enStatus].height()*0.32,m_enStatusPM[m_enStatus]);
    qp.drawText(m_enStatusPM[m_enStatus].width()*0.32, m_enStatusPM[m_enStatus].height()*0.32/2,"Energy: " + QString::number(m_robot->getEnergy()));
    qp.drawText(m_enStatusPM[m_enStatus].width()*0.32+100, m_enStatusPM[m_enStatus].height()*0.32/2,"Score: " + QString::number(m_robot->getScore()));
    qp.drawText(m_enStatusPM[m_enStatus].width()*0.32+200, m_enStatusPM[m_enStatus].height()*0.32/2,"Steps: " + QString::number(m_robot->getSteps()));
    qp.drawText(m_enStatusPM[m_enStatus].width()*0.32+300, m_enStatusPM[m_enStatus].height()*0.32/2,"States: " + QString::number(m_robot->getStates()));
    qp.drawText(m_enStatusPM[m_enStatus].width()*0.32+400, m_enStatusPM[m_enStatus].height()*0.32/2,"ShortWay: " + QString::number(m_robot->getTrueWay()));

}

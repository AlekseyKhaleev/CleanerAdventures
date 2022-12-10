#include "status.h"
#include "Robot.h"
#include <QTimerEvent>
#include <QPainter>

Status::Status(){

}

void Status::timerEvent(QTimerEvent *event){
    if(event->timerId() == m_timer){
        repaint();
    }
}

void Status::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    drawStatus();
}

void Status::drawStatus(){
    QPainter qp(this);

    qp.drawText(70, 70,"text");

}

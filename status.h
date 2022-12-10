#pragma once

#include <QWidget>
#include "Robot.h"

class Status : public Robot
{
public:
    Status();
private:
    enum Energy{
        en_0, en_10, en_25, en_50, en_75, en_90, en_100
    } m_enStatus;

    QVector<QPixmap> m_enStatusPM{
        QPixmap("../icons/en_0"),
        QPixmap("../icons/en_10"),
        QPixmap("../icons/en_25"),
        QPixmap("../icons/en_50"),
        QPixmap("../icons/en_75"),
        QPixmap("../icons/en_90"),
        QPixmap("../icons/en_100")
    };

    void timerEvent(QTimerEvent *event)  override;
    void paintEvent(QPaintEvent *event)  override;

    void drawStatus();
};


#pragma once

#include <QWidget>
#include "Robot.h"
#include <QObject>
#include <QLabel>

class EnergyWidget : public QLabel
{
//    Q_OBJECT
public:
    EnergyWidget(Robot *object);
private:
    static const int STATUS_HEIGHT = 70;
    int m_statTimer;
    Robot *m_robot;
    enum Energy{
        en_0, en_10, en_30, en_50, en_70, en_80, en_90
    } m_enStatus;

    QVector<QPixmap> m_enStatusPM{
        QPixmap("../icons/en_0"),
        QPixmap("../icons/en_10"),
        QPixmap("../icons/en_30"),
        QPixmap("../icons/en_50"),
        QPixmap("../icons/en_70"),
        QPixmap("../icons/en_80"),
        QPixmap("../icons/en_90")
    };

    void timerEvent(QTimerEvent *event)  override;
    void paintEvent(QPaintEvent *event)  override;

    void setEnergyStatus();
    void drawStatus();
};


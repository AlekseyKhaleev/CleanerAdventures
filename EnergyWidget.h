#pragma once

#include <QObject>
#include <QWidget>
#include <QLabel>

class EnergyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EnergyWidget(QWidget *parent=nullptr);
    ~EnergyWidget();

    void paintEvent(QPaintEvent *event)  override;

signals:
    void statusChanged();

public slots:
    void setEnergyStatus(int energy);

private:
    enum Energy{
        en_0, en_10, en_30, en_50, en_70, en_80, en_90
    } m_enStatus;

    QVector<QImage> m_enStatusPM{
        QImage("../icons/en_0"),
        QImage("../icons/en_10"),
        QImage("../icons/en_30"),
        QImage("../icons/en_50"),
        QImage("../icons/en_70"),
        QImage("../icons/en_80"),
        QImage("../icons/en_90")
    };
    void drawStatus();
};


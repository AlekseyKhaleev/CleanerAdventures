#pragma once

#include <QLabel>
#include <QObject>
#include <QWidget>

class EnergyWidget : public QWidget {
Q_OBJECT
public:
    explicit EnergyWidget(QWidget *parent = nullptr);

    ~EnergyWidget() override;

signals:

    void statusChanged();

public slots:

    void paintEvent(QPaintEvent *event) override;
    void setEnergyStatus(int energy);

private:
    enum Energy {
        en_0, en_10, en_30, en_50, en_70, en_80, en_90
    } m_enStatus;

    QVector<QImage*> m_enStatusImgs;

    void drawStatus();
};


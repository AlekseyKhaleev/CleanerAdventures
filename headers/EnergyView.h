#pragma once

#include <QLabel>
#include <QObject>
#include <QWidget>

#include "RobotView.h"

class EnergyView : public RobotView {

Q_OBJECT

public:
    explicit EnergyView(const Robot::Model &targetModel, RobotView *parent = nullptr);

    ~EnergyView() override;

public slots:

    void updateModel(Robot::Model model) override;

private:

    void paintEvent(QPaintEvent *event) override;

    void setEnergyStatus();

    enum Energy {
        en_0, en_10, en_30, en_50, en_70, en_80, en_90
    } m_enStatus;

    QVector<QImage*> m_enStatusImgs;

    void drawStatus();
};

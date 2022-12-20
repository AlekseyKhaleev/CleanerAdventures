#pragma once

#include <QLCDNumber>
#include <QWidget>

#include "RobotView.h"

class ScoreView : public RobotView{
Q_OBJECT

public:
    ScoreView(int numDigits, const Robot::Model &targetModel, RobotView *parent = nullptr);

    ~ScoreView() override;

signals:
    void levelUpdated(int level);

public slots:

    void paintEvent(QPaintEvent * event) override;
    void updateModel(Robot::Model model) override;
private:
    QLCDNumber *m_viewItem;
};





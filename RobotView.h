#pragma once

#include <QWidget>

#include "RobotModel.h"

using namespace Robot;

class RobotView :public QWidget{

Q_OBJECT

public slots:
    void updateModel(Model currentModel);
signals:
    void keyHandled(QKeyEvent event);

public:
    explicit RobotView(const Model &targetModel, QWidget *parent= nullptr);
    ~RobotView() override;
private:

    Model *m_viewModel;
    static const int ANIMATION_DELAY = 300;
    int m_animationTimerId;
    QVector<QImage*> m_white;
    QVector<QImage*> m_green;
    QVector<QImage*> m_yellow;
    QVector<QImage*> m_red;
    QVector<QVector<QImage*>> m_robotSkin{m_white, m_green, m_yellow, m_red};

    void timerEvent(QTimerEvent *event)  override;
    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

    void drawRobot();
};



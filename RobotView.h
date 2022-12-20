#pragma once

#include <QWidget>

#include "RobotModel.h"



class RobotView :public QWidget{

Q_OBJECT

signals:
    void keyHandled(QKeyEvent event);

public slots:
    virtual void updateModel(Robot::Model model);

public:
    explicit RobotView(const Robot::Model &targetModel, QWidget *parent= nullptr);
    ~RobotView() override;

private:
    Robot::Model m_viewModel;
    QVector<QImage*> m_white;
    QVector<QImage*> m_green;
    QVector<QImage*> m_yellow;
    QVector<QImage*> m_red;
    QVector<QVector<QImage*>> m_robotSkin{m_white, m_green, m_yellow, m_red};


    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

    void drawRobot();
};



#pragma once

#include <QWidget>

#include "MazeModel.h"


class MazeView : public QWidget{

    Q_OBJECT
public:
    explicit MazeView(const Maze::Model &targetModel, QWidget *parent= nullptr);
    ~MazeView() override;
public slots:
    void paintEvent(QPaintEvent *event) override;
    void updateModel();

private:
    const Maze::Model *m_viewModel;
    QImage *m_batteryImage;
    QImage *m_targetImage;

    void drawMaze();
    void drawTarget();
    void drawBattery();

};




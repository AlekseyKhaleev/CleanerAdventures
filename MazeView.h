#pragma once

#include <QWidget>

#include "MazeModel.h"

using namespace Maze;

class MazeView : public QWidget{

    Q_OBJECT
public:
    explicit MazeView(const Model &targetModel, QWidget *parent= nullptr);
    ~MazeView() override;
private:
    const Model *m_viewModel;
    QImage *m_batteryImage;
    QImage *m_targetImage;
    void paintEvent(QPaintEvent *event) override;
    void drawMaze();
    void drawTarget();
    void drawBattery();

};




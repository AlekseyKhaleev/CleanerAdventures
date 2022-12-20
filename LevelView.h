#pragma once

#include <QLCDNumber>
#include <QWidget>
#include "MazeView.h"

class LevelView : public MazeView{

Q_OBJECT

public:
    LevelView(int numDigits, const Maze::Model &targetModel, MazeView *parent = nullptr);

    ~LevelView() override;

signals:
    void levelUpdated(int level);

public slots:
    void updateModel(Maze::Model model) override;
    void paintEvent(QPaintEvent *event) override;

private:
    QLCDNumber *m_viewItem;
};

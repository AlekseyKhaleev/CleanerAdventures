#include "headers/LevelView.h"
#include "QVBoxLayout"

LevelView::LevelView(int numDigits, const Maze::Model &targetModel, MazeView *parent )
        :m_viewItem(new QLCDNumber(numDigits)), MazeView(targetModel, parent)
{
    m_viewItem->setSegmentStyle(QLCDNumber::Filled);
    connect(this, &LevelView::levelUpdated, m_viewItem, qOverload<int>(&QLCDNumber::display));
    auto *levelLayout = new QHBoxLayout;
    levelLayout->addWidget(m_viewItem);
    setLayout(levelLayout);
    repaint();
}

void LevelView::updateModel(Maze::Model model) {
    m_viewModel = model;
    emit levelUpdated(m_viewModel.level);
}

void LevelView::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    emit levelUpdated(m_viewModel.level);
}

LevelView::~LevelView()=default;

#include "ScoreView.h"
#include "QHBoxLayout"

ScoreView::ScoreView(int numDigits, const Robot::Model &targetModel, RobotView *parent )
:m_viewItem(new QLCDNumber(numDigits)), RobotView(targetModel, parent)
{
    m_viewItem->setSegmentStyle(QLCDNumber::Filled);
    connect(this, &ScoreView::levelUpdated, m_viewItem, qOverload<int>(&QLCDNumber::display));
    auto *itemLayout = new QHBoxLayout;
    itemLayout->addWidget(m_viewItem);
    setLayout(itemLayout);
    repaint();
}

void ScoreView::updateModel(Robot::Model model) {
    m_viewModel = model;
    emit levelUpdated(m_viewModel.score);
}

void ScoreView::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    emit levelUpdated(m_viewModel.score);
}

ScoreView::~ScoreView()=default;

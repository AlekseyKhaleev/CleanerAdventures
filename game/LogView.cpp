

#include "LogView.h"

#include <QVBoxLayout>
#include <utility>


LogView::LogView(Robot::Model targetModel, QWidget *parent): RobotView(std::move(targetModel), parent), m_logs(new QListWidget)

{
//    this->setContentsMargins(0,0,0,0);
    m_logs->setStyleSheet("border: 6px solid white; font: bold; font-size: 14px");
    m_logs->addItem(m_viewModel.state);
    m_logs->setFocusPolicy(Qt::NoFocus);
//    m_logs->setContentsMargins(50,0,0,0);
    m_logs->setWindowFlag(Qt::FramelessWindowHint);

    m_logs->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored);

    auto layout = new QVBoxLayout;
    layout->addWidget(m_logs);
    setLayout(layout);
}

void LogView::updateModel(Robot::Model model) {
    if(model.state != m_viewModel.state) {
        m_viewModel = model;

        m_logs->addItem(m_viewModel.state);
        m_logs->scrollToBottom();
    }
}


LogView::~LogView()=default;

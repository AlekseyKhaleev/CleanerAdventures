//
// Created by kristofer on 22.12.22.
//

#include "MainWidget.h"

#include <QStackedLayout>
#include <QWidget>

MainWidget::MainWidget(QWidget *parent):
QWidget(parent), m_menu(new MenuWidget), m_game(new GameWidget), m_layout(new QStackedLayout)
{
    connect(m_menu, &MenuWidget::widgetsChanged, this, &MainWidget::changeWidgets);
    connect(m_game, &GameWidget::widgetsChanged, this, &MainWidget::changeWidgets);


    m_layout->setStackingMode(QStackedLayout::StackOne);

    m_layout->addWidget(m_menu);
    m_layout->addWidget(m_game);

    setLayout(m_layout);
}

void MainWidget::changeWidgets() {
    if(m_layout->currentWidget() == m_menu){
        m_layout->setCurrentWidget(m_game);
    }
    else{
        m_layout->setCurrentWidget(m_menu);
    }
}

MainWidget::~MainWidget()=default;

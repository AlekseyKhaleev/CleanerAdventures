//
// Created by kristofer on 22.12.22.
//

#include "MainWidget.h"

#include <QCoreApplication>
#include <QStackedLayout>
#include <QWidget>

MainWidget::MainWidget(QWidget *parent):
QWidget(parent), m_menu(new MenuWidget), m_game(new GameWidget), m_layout(new QStackedLayout)
{
    this->setStyleSheet("QWidget {background-color: black; color: WHITE;}");

    connect(m_menu, &MenuWidget::widgetsChanged, this, &MainWidget::changeWidgets);
    connect(m_menu, &MenuWidget::exitClicked, this, &MainWidget::exit);
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

void MainWidget::exit() {
    QCoreApplication::quit();
}

MainWidget::~MainWidget()=default;

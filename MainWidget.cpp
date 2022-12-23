//
// Created by kristofer on 22.12.22.
//

#include "MainWidget.h"

#include <QCoreApplication>
#include <QInputDialog>
#include <QStackedLayout>
#include <QWidget>


using namespace Menu;

MainWidget::MainWidget(QWidget *parent):
QWidget(parent), m_menu(new MenuWidget), m_layout(new QStackedLayout), m_controls(new ConrolsView)
{
    this->setStyleSheet("QWidget {background-color: black; color: WHITE;}");

    connect(m_menu, SIGNAL(newGameClicked(int)), this, SLOT(changeWidgets(int)));
    connect(m_menu, SIGNAL(controlsClicked(int)), this, SLOT(changeWidgets(int)));
    connect(m_menu, SIGNAL(highscoresClicked(int)), this, SLOT(changeWidgets(int)));
    connect(m_menu, SIGNAL(aboutClicked(int)), this, SLOT(changeWidgets(int)));
    connect(m_menu, SIGNAL(exitClicked(int)), this, SLOT(changeWidgets(int)));
    connect(m_menu, SIGNAL(returnClicked(int)), this, SLOT(changeWidgets(int)));
    connect(m_controls, SIGNAL(returnClicked(int)), this, SLOT(changeWidgets(int)));


    m_layout->setStackingMode(QStackedLayout::StackOne);

    m_layout->addWidget(m_menu);
    m_layout->addWidget(m_controls);

    setLayout(m_layout);
}

void MainWidget::changeWidgets(int button) {
    switch(button){
        case Menu::NEW_GAME:{
//            QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
//                                                 tr("User name:"), QLineEdit::Normal,
//                                                 setOption(QInputDialog::NoButtons);

            QInputDialog auth;
            auth.setOption(QInputDialog::NoButtons);
//            auth.setOption()
            auth.setInputMode(QInputDialog::TextInput);
            auth.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//            auth.resize(2000,2000);

            auto const rec = QGuiApplication::primaryScreen()->size();
//            auth.setMaximumSize(rec);
//            auth.setFixedSize(rec);

            auth.setLabelText("Enter your name, robot :");

            auth.setStyleSheet("border: 6px solid white; font: bold; font-size: 24px; "
                               "color: white; background-color: black; width: 360px; height: 480px;");
//            auth.resize(20,2000);

            auth.exec();
            QString name = auth.textValue();
//            QString name = QInputDialog::getText(nullptr,tr(""),tr("Enter your name, robot:"));
            delete m_game;
            m_game = new GameWidget(name);
            connect(m_game, SIGNAL(returnClicked(int)), this, SLOT(changeWidgets(int)));
            m_layout->addWidget(m_game);
        }
        case Menu::RETURN:{
            if(m_layout->currentWidget() == m_menu && m_game){ m_layout->setCurrentWidget(m_game); }
            else{ m_layout->setCurrentWidget(m_menu); }
            break;
        }
        case Menu::CONTROLS:{ m_layout->setCurrentWidget(m_controls); break; }
        case Menu::EXIT: QCoreApplication::quit();
        default:break;
    }

}


MainWidget::~MainWidget()=default;

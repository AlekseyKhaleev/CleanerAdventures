
#include "MenuWidget.h"

#include<QPushButton>
#include <QWidget>
#include <QVBoxLayout>
#include <QKeyEvent>


MenuWidget::MenuWidget(QWidget *parent): QWidget(parent)
{
    auto layout = new QVBoxLayout;
    layout->addWidget(new QPushButton("Resume"));
    layout->addWidget(new QPushButton("New game"));
    layout->addWidget(new QPushButton("Control keys"));
    layout->addWidget(new QPushButton("Highscores"));
    layout->addWidget(new QPushButton("About"));
    layout->addWidget(new QPushButton("Exit"));

    setLayout(layout);

}

void MenuWidget::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Escape){
        emit widgetsChanged();
    }

}


MenuWidget::~MenuWidget()=default;


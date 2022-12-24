#include "ControlsWidget.h"

#include <QGridLayout>
#include <QKeyEvent>
#include <QLabel>


ControlsWidget::ControlsWidget(QWidget *parent): QWidget(parent)
{
//    this->setStyleSheet("background-color: white");

    auto layout = new QGridLayout;

    auto title = new QLabel("Control keys:");
    title->setStyleSheet("QLabel { font: bold solid black; font-size: 72px; }");
    title->setAlignment(Qt::AlignCenter);

    layout->addWidget(title, 0, 0, 2, 2);
    layout->addWidget(createLabel("Rotate robot : "), 2,0,1,1);
    layout->addWidget(createLabel("Arrows"),2,1,1,1);
    layout->addWidget(createLabel("Move robot : "), 3,0,1,1);
    layout->addWidget(createLabel("Space"),3,1,1,1);
    layout->addWidget(createLabel("Step Undo : "),4,0,1,1);
    layout->addWidget(createLabel("Backspace"), 4,1,1,1);
    layout->addWidget(createLabel("Menu / Return : "), 5,0,1,1);
    layout->addWidget(createLabel("ESC"), 5,1,1,1);
    setLayout(layout);

}

void ControlsWidget::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        emit returnClicked();
    }
}



QLabel *ControlsWidget::createLabel(const QString &text){
    auto *label = new QLabel(text);
    label->setStyleSheet("QLabel { font: bold; font-size: 48px; }");
    label->setAlignment(Qt::AlignCenter);
    return label;
}

ControlsWidget::~ControlsWidget()=default;


#include "HighscoresWidget.h"

#include <QKeyEvent>
#include <QLabel>

HighscoresWidget::HighscoresWidget(QWidget *parent) : QWidget(parent)
{
    auto layout = new QGridLayout;

    auto title = new QLabel("Highscores :");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("QLabel { font: bold; font-size: 72px }");

    layout->addWidget(title);
    setLayout(layout);

}

void HighscoresWidget::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        emit returnClicked();
    }
}

HighscoresWidget::~HighscoresWidget()=default;
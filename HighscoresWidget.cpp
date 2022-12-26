
#include "HighscoresWidget.h"

#include <QFile>
#include <QKeyEvent>
#include <QLabel>


HighscoresWidget::HighscoresWidget(QWidget *parent) : QWidget(parent), m_highscores(new QFile(":/highscores.txt"))
{
    readHighscores();
    auto layout = new QGridLayout;

    auto title = new QLabel("Highscores :");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("QLabel { font: bold; font-size: 72px }");

    layout->addWidget(title, 0, 0, 4, 5);
    for (int i=0; i<10;i++){
        layout->addWidget(createLabel(QString::number(i+1) + ". "), 4+i, 1,1,1, Qt::AlignRight);
        layout->addWidget(createLabel(m_lines[i].NAME), 4+i, 2,1,1);
        layout->addWidget(createLabel(QString::number(m_lines[i].SCORE)), 4+i, 3,1,1);

    }
    setLayout(layout);

}

void HighscoresWidget::readHighscores(){
    if (!m_highscores->open(QIODevice::ReadOnly | QIODevice::Text)){return;}
    m_lines.clear();
    while(!m_highscores->atEnd()) {
        QString lineName = m_highscores->readLine();
        lineName.remove('\n');
        QString lineScore = m_highscores->readLine();
        lineName.remove('\n');
        m_lines.push_back(line(lineName, lineScore.toInt()));
    }
    std::sort(m_lines.begin(), m_lines.end(), compareLines);
    m_highscores->close();
}

void HighscoresWidget::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        emit returnClicked();
    }
}

QLabel *HighscoresWidget::createLabel(const QString &text) {
    auto *label = new QLabel(text);
    label->setStyleSheet("QLabel { font: bold; font-size: 32px }");
    label->setAlignment(Qt::AlignLeft);
    label->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Ignored);
    return label;
}

HighscoresWidget::~HighscoresWidget()=default;
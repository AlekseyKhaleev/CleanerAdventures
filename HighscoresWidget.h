#pragma once

#include "MenuWidget.h"

#include <QFile>
#include <QLabel>
#include <QMap>
#include <QWidget>
#include <utility>



class HighscoresWidget : public QWidget {

Q_OBJECT

public:
    explicit HighscoresWidget(QWidget *parent= nullptr);
    ~HighscoresWidget() override;
signals:
    void returnClicked(int button=Menu::RETURN);

public slots:
    void keyPressEvent(QKeyEvent *event) override;
    void readHighscores();

private:
    struct line{
        QString NAME;
        int SCORE;
        line(QString name, int score){
            NAME = std::move(name);
            SCORE = score;
        }
    };
    static bool compareLines(const line &first, const line &second){
        return first.SCORE > second.SCORE;
    }
    QFile *m_highscores;
    QVector<line> m_lines;

    QLabel *createLabel(const QString &text);


};


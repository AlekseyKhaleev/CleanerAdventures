#pragma once

#include <QWidget>

#include "MenuWidget.h"

class HighscoresWidget : public QWidget {

Q_OBJECT

public:
    explicit HighscoresWidget(QWidget *parent= nullptr);
    ~HighscoresWidget() override;
signals:
    void returnClicked(int button=Menu::RETURN);

public slots:
    void keyPressEvent(QKeyEvent *event) override;
};


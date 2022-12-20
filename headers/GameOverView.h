
#pragma once

#include <QMessageBox>

#include "RobotView.h"


class GameOverView : public QMessageBox {

    Q_OBJECT

public:
    explicit GameOverView(QMessageBox *parent = nullptr);

    ~GameOverView() override;

signals:
    void gameStarted(int levelIncrease);
    void gameEnded();

public slots:
    void levelDefeated();
    void levelDone();
};

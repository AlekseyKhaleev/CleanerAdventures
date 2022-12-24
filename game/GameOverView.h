
#pragma once

#include <QMessageBox>


class GameOverView : public QMessageBox {

    Q_OBJECT

public:
    explicit GameOverView(QMessageBox *parent = nullptr);

    ~GameOverView() override;

signals:
    void gameStarted();
    void gameEnded();

public slots:
    void levelLost();
    void levelDone();
};

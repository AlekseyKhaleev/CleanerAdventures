#pragma once

#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>


class MenuWidget: public QWidget {
Q_OBJECT

public:
    explicit MenuWidget(QWidget *parent = nullptr);

    ~MenuWidget() override;

signals:
    void widgetsChanged();
    void newGameClicked();
    void controlsClicked();
    void highscoresClicked();
    void aboutClicked();
    void exitClicked();

public slots:
    void keyPressEvent(QKeyEvent *event) override;

private:
    QPushButton *m_newGame;
    QPushButton *m_controls;
    QPushButton *m_highscores;
    QPushButton *m_about;
    QPushButton *m_exit;

    QPushButton *createButton(const QString &text);


};

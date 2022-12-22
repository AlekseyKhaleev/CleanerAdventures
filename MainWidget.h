#pragma once

#include <QMainWindow>

#include <QStackedLayout>

#include "MenuWidget.h"
#include "GameWidget.h"

class MainWidget: public QWidget {

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget() override;
private:
    MenuWidget *m_menu;
    GameWidget *m_game;
    QStackedLayout *m_layout;
public slots:
    void changeWidgets();
};



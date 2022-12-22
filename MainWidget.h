#pragma once

#include <QMainWindow>

#include <QStackedLayout>

#include "MenuWidget.h"
#include "GameWidget.h"
#include "ConrolsView.h"

namespace {

}
class MainWidget: public QWidget {
Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget() override;
private:

    MenuWidget *m_menu;
    GameWidget *m_game;
    ConrolsView *m_controls;
    QStackedLayout *m_layout;

public slots:
    void changeWidgets(int button);
};



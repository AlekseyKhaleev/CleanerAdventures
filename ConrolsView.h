#pragma once

#include <QWidget>
#include <QTableView>

#include "MenuWidget.h"

class ConrolsView: public QTableView {
    Q_OBJECT
public:
    explicit ConrolsView(QTableView *parent=nullptr);
    ~ConrolsView() override;

signals:
    void returnClicked(int button=Menu::RETURN);

public slots:
    void keyPressEvent(QKeyEvent *event) override;
protected:

};

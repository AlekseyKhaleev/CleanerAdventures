//
// Created by kristofer on 22.12.22.
//

#include "ConrolsView.h"

#include <QKeyEvent>

ConrolsView::ConrolsView(QTableView *parent): QTableView(parent)
{
    this->setStyleSheet("background-color: white");
}

void ConrolsView::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        emit returnClicked();
    }
}

ConrolsView::~ConrolsView()=default;

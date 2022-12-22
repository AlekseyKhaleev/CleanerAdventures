#pragma once

#include <QVBoxLayout>
#include <QWidget>

class MenuWidget: public QWidget {
Q_OBJECT

public:
    explicit MenuWidget(QWidget *parent = nullptr);

    ~MenuWidget() override;

signals:
    void widgetsChanged();

public slots:
    void keyPressEvent(QKeyEvent *event) override;

private:


};

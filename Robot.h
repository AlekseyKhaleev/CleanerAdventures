#pragma once

#include <iostream>
#include <memory>
#include <QPoint>
#include "Map.h"

/***************************** Определения для удобства работы с классами *********************************************/
//class IFsm;
//using FsmPtr = std::shared_ptr<IFsm>;
//typedef bool signal[2];

///**********************************************************************************************************************/

//class IFsm {
//protected:
//    virtual ~IFsm() = default; // защищенный деструктор
//    IFsm& operator=(const IFsm&) = default; // запрет присваивания
//    [[nodiscard]] static FsmPtr CreateInstance(); // функция-фабрика

//    virtual void SetState(bool (*state)())=0;
//    virtual void Update()=0;
//public:
//    virtual QPoint SigHandle(signal sig)=0;

//};



class Robot : public Map{
private:
    QPoint m_pos;
    enum Directions{
        left, right, up, down
    } m_dest;
    QVector<QPixmap> DirIcons{
                QPixmap("../icons/rocket_left"),
                QPixmap("../icons/rocket_right"),
                QPixmap("../icons/rocket_up"),
                QPixmap("../icons/rocket_down"),
    };

    bool (*ActiveState)()= nullptr; // указатель на активное состояние автомата

    void SetState(bool (*state)());
    void Update();

    static bool wait();
    static bool analyze();
    static bool turn();

    static bool exit();
    static bool g_left();
    static bool g_right();
    void locateSelf();
    void initRobot();
    void moveRobot();
    bool checkWall(QPoint dest);


    void timerEvent(QTimerEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void doPainting();
public:
//    QPoint SigHandle(signal sig) override;
    Robot();           // открытый конструктор
    ~Robot() override; // открытый деструктор
};



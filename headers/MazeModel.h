#pragma once

#include <QGuiApplication>
#include <QMap>
#include <QObject>
#include <QPoint>
#include <QScreen>
#include <QSet>
#include <QVector>
#include <QWidget>

inline uint qHash(const QPoint &key) { return (key.x() << 16) + key.y(); }

namespace Maze {

    struct Model {
        static const int DOT_SIDE{34};
        int level{1}, fieldWidth{}, fieldHeight{};

        QSet<QPoint> walls, cells;
        QVector<QPoint> batteries;
        QPoint targetPosition;
        Model() = default;
    };

    class MazeModel : public QObject {

    Q_OBJECT

    public:
        explicit MazeModel(QObject *parent = nullptr);
        ~MazeModel() override;

    signals:
        void modelChanged(Maze::Model model);

    public slots:
        void addBattery(QPoint value);

        void delBattery(QPoint value);

        void setMazeState(const Maze::Model &state);

        void initMaze(int levelIncrease=0);

        Model getMazeModel();

    private:
        Model *m_mazeState;

        QPoint getRandDot();



        static QVector<QPoint> getMazeNeighbours(QPoint current, const QSet<QPoint> &cells);

        void initFieldSize();

        void initDefaultMazeMap();

        void locateWalls();
    };
}


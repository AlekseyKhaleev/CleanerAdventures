#pragma once

#include <QGuiApplication>
#include <QMap>
#include <QObject>
#include <QPoint>
#include <QVector>
#include <QScreen>
#include <QSet>
#include <QWidget>

inline uint qHash(const QPoint &key) { return (key.x() << 16) + key.y(); }

namespace Maze {

    struct Model {

        QSet<QPoint> walls, cells;
        QVector<QPoint> batteries;
        QPoint targetPosition;
        int level{1}, fieldWidth, fieldHeight;
        static const int DOT_SIDE{34};
        Model() = default;
    };

    class MazeModel : public QWidget {

    Q_OBJECT

    public:
        explicit MazeModel(QWidget *parent = nullptr);
        ~MazeModel() override;

    signals:
        void modelChanged();

    public slots:
        void addBattery(QPoint value);

        void delBattery(QPoint value);

        void setMazeState(const Model &state);

    private:
        Model *m_mazeState;

        QPoint getRandDot();

        void initMaze();

        static QVector<QPoint> getMazeNeighbours(QPoint current, const QSet<QPoint> &cells);

        void initFieldSize();

        void initDefaultMazeMap();

        void locateWalls();

        Model getMazeModel();
    };
}


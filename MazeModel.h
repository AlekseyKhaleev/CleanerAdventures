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
        int level{0}, fieldWidth, fieldHeight;
        static const int DOT_SIDE{34};
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

        Model& getMazeModel() const;

    private:
        Model *m_mazeState;

        QPoint getRandDot();

        void initMaze();

        static QVector<QPoint> getMazeNeighbours(QPoint current, const QSet<QPoint> &cells);

        void initFieldSize();

        void initDefaultMazeMap();

        void locateWalls();
    };
}


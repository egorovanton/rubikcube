#ifndef DIRECTION_H
#define DIRECTION_H

#include <QString>
#include <QVector>


enum Rotation {
    COUNTER_CLOCKWISE = 1,
    HALF_TURN = 2,
    CLOCKWISE = 3
};

enum PlaneType {
    FRONT = 0,
    RIGHT = 1,
    UP = 2,
    BACK = 3,
    LEFT = 4,
    DOWN = 5
};

class Direction
{

private:
    PlaneType plane;
    Rotation rotation;
    QVector<PlaneType> neighbours;

public:
    Direction(QString str);
    Direction(PlaneType p, Rotation r);

    QVector<PlaneType> getNeighbours();


    Rotation getRotation() const;
    PlaneType getPlane() const;
};


#endif // DIRECTION_H

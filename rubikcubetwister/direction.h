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
    UP = 0,
    RIGHT = 1,
    BACK = 2,
    DOWN = 3,
    FRONT = 5,
    LEFT = 4
};



class Direction
{

private:
    PlaneType plane;
    Rotation rotation;
    QVector<PlaneType> neighbours;

public:
    Direction(QString str);

    QVector<PlaneType> getNeighbours();


    Rotation getRotation() const;
    PlaneType getPlane() const;
};


#endif // DIRECTION_H

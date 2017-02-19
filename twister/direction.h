#ifndef DIRECTION_H
#define DIRECTION_H

#include <QString>
#include <QSet>
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
    DOWN = 5,

    STANDING = 6,
    MIDDLE = 7,
    EQUATOR = 8,

//    WHOLE_X  = 9,
    WHOLE_Y = 10,
//    WHOLE_Z = 11,

    STUB = -1
};

using Duo    = std::tuple<PlaneType, PlaneType>;
using Triple = std::tuple<PlaneType, PlaneType, PlaneType>;

class Direction
{

private:
    PlaneType plane;
    Rotation rotation;
    QVector<PlaneType> neighbours;

public:
    static const QSet<QString> validDirecions;

    Direction(QString str);
    Direction(PlaneType p, Rotation r);

    QVector<PlaneType> getNeighbours();


    Rotation getRotation() const;
    PlaneType getPlane() const;

    QString merge(Direction d);
};


#endif // DIRECTION_H

#include "direction.h"
#include "utils.h"
#include <QDebug>


PlaneType Direction::getPlane() const
{
    return plane;
}

Direction::Direction(QString str)
{
//    if (str.isEmpty()) {
//        throw IlligalDirection("Empty string argument in constructor");
//    }

    switch (str[0].toLatin1()) {
    case 'F':
        plane = FRONT;
        break;
    case 'R':
        plane = RIGHT;
        break;
    case 'U':
        plane = UP;
        break;
    case 'B':
        plane = BACK;
        break;
    case 'L':
        plane = LEFT;
        break;
    case 'D':
        plane = DOWN;
        break;
    case 'M':
        plane = MIDDLE;
        break;
    case 'E':
        plane = EQUATOR;
        break;
    case 'S':
        plane = STANDING;
        break;
    }

    if (str.length()  == 1) {
        rotation = CLOCKWISE;
    } else {
        switch (str[1].toLatin1()) {
        case '\'':
            rotation = COUNTER_CLOCKWISE;
            break;
        case '2':
            rotation = HALF_TURN;
            break;
        default:
            break;
        }
    }


}

Direction::Direction(PlaneType p, Rotation r): plane(p), rotation(r) {}

// fixme return neighbours in correct order
QVector<PlaneType> Direction::getNeighbours()
{
//    qDebug() << "Direction::getNeighbours plane = " << plane << " rotation = " << rotation;
    if (neighbours.isEmpty()) {
//        qDebug() << "Direction::getNeighbours neighbours is empty";
        for(int n: QVector<int>{2, 1, -1, -2}) {
//            qDebug() << "Direction::getNeighbours " << modulus(plane + n * (plane % 2 ? -1 : 1), 6);
            neighbours.push_back(static_cast<PlaneType>(modulus(plane + n * (plane % 2 ? -1 : 1), 6)));
        }
        if (plane == STANDING) {
            std::reverse(neighbours.begin(), neighbours.end());
        }
    }

    return neighbours;
}

Rotation Direction::getRotation() const
{
    return rotation;
}

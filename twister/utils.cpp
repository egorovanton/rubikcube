#include "utils.h"
#include "direction.h"

template<>
QString vectorToString(QVector<int> const &vector) {
    QString result;
    for (int t: vector) {
        result += QString::number(t);
    }
    return result;
}


void rotateHelper(int n, int &x, int &y) {
    int temp = y;
    y = x;
    x = n - temp - 1;
}

PlaneType getLeft(PlaneType p) {
    switch (p) {
        case FRONT:
            return LEFT;
        case LEFT:
            return BACK;
        case BACK:
            return RIGHT;
        case RIGHT:
            return FRONT;
        default:
            return STUB;
    }
}

PlaneType getRight(PlaneType p) {
    switch (p) {
        case FRONT:
            return RIGHT;
        case RIGHT:
            return BACK;
        case BACK:
            return LEFT;
        case LEFT:
            return FRONT;
        default:
            return STUB;
    }
}

PlaneType getBack(PlaneType p) {
    switch (p) {
        case FRONT:
            return BACK;
        case BACK:
            return FRONT;
        case LEFT:
            return RIGHT;
        case RIGHT:
            return LEFT;
        default:
            return STUB;
    }
}

QString planeToString(PlaneType p) {
    switch (p) {
        case DOWN:
            return "D";
        case FRONT:
            return "F";
        case RIGHT:
            return "R";
        case UP:
            return "U";
        case BACK:
            return "B";
        case LEFT:
            return "L";
        default:
            return "kiddo something broken wow such unexpected";
    }
}



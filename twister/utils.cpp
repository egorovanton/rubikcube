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

std::string printTuple(const std::tuple<PlaneType, PlaneType, PlaneType> &t, const std::string &sep) {
    using std::get;

    std::string result;
    result += planeToString(get<0>(t)).toStdString();
    result += sep;
    result += planeToString(get<1>(t)).toStdString();
    result += sep;
    result += planeToString(get<2>(t)).toStdString();
    return result;
}

std::string printTuple(const std::tuple<PlaneType, PlaneType> &t, const std::string &sep) {
    using std::get;

    std::string result;
    result += planeToString(get<0>(t)).toStdString();
    result += sep;
    result += planeToString(get<1>(t)).toStdString();
    return result;
}



QVector<PlaneType> toVector(const PlaneType p) {
    return {p};
}

QVector<PlaneType> toVector(const Duo &d) {
    using std::get;
    return {get<0>(d), get<1>(d)};
}

QVector<PlaneType> toVector(const Triple &t) {
    using std::get;
    return {get<0>(t), get<1>(t), get<2>(t)};
}

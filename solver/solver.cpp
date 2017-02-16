//
// Created by Vetrier on 14/02/2017.
//

#include "solver.h"

#include <iostream>

QStringList Solver::solve() {

    cross();
    return result;

}

void Solver::cross() {
    bool changes = true;
    while (changes) {
        changes = false;
        for (auto c:sides) {
            if (result.isEmpty() || result.last() != "|")
                result << "|";
            changes = upPlane(c) || downPlane(c) || midPlane(c) || changes;
        }
    }
}

bool Solver::upPlane(PlaneType currentSide) {
    auto tuple = cube.getCubie(UP, currentSide);

    if (std::get<0>(tuple) == DOWN) {
        PlaneType &cubieSide = std::get<1>(tuple);
        rotate(topTwist(currentSide, cubieSide));
        rotate(planeToString(cubieSide) + "2");
        return true;
    } else if (std::get<1>(tuple) == DOWN) {
        PlaneType &cubieSide = std::get<0>(tuple);
        if (cubieSide == getLeft(currentSide)) {
            dropTopLeft(currentSide);
        } else if (cubieSide == getRight(currentSide)) {
            dropTopRight(currentSide);
        } else {
            rotate("U");
            PlaneType l = getLeft(currentSide);
            cubieSide == currentSide ? dropTopRight(l) : dropTopLeft(l);
            rotate("U'");
        }
        return true;
    }

    return false;
}

bool Solver::downPlane(PlaneType currentSide) {
    auto tuple = cube.getCubie(DOWN, currentSide);
    if (std::get<0>(tuple) == DOWN) {
        PlaneType &cubieSide = std::get<1>(tuple);
        if (cubieSide != currentSide) {
            rotate(planeToString(currentSide) + "2");
            return true;
        }
    } else if (std::get<1>(tuple) == DOWN) {
        PlaneType &cubieSide = std::get<0>(tuple);
        for (auto s : QVector<QString>{planeToString(currentSide) + "'", "U'",
                                       planeToString(getRight(currentSide)), "U"}) {
            rotate(s);
        }
        return true;
    }
    return false;
}


bool Solver::midPlane(PlaneType currentSide) {
    auto tuple = cube.getCubie(currentSide, getRight(currentSide));
    if (std::get<1>(tuple) == DOWN) {
        if (std::get<0>(tuple) == currentSide)
            rotate(planeToString(currentSide));
        else
            rotate(planeToString(currentSide) + "'");
        return true;
    } else if (std::get<0>(tuple) == DOWN) {
        rotate("U'");
        rotate(planeToString(getRight(currentSide)));
        rotate("U");
        rotate(planeToString(getRight(currentSide)) + "'");

        if (std::get<1>(tuple) == currentSide)
            rotate(planeToString(currentSide) + "2");
        return true;
    }
    return false;
}


void Solver::dropTopLeft(PlaneType cur) {
    const QString &L = planeToString(getLeft(cur));
    const QString &sCur = planeToString(cur);
    for (auto s : QVector<QString>{sCur + "'", L, sCur})
        rotate(s);
}

void Solver::dropTopRight(PlaneType cur) {
    const QString &R = planeToString(getRight(cur));
    const QString &sCur = planeToString(cur);
    for (auto s : QVector<QString>{sCur, R + "'", sCur + "'"})
        rotate(s);
}

QString Solver::topTwist(PlaneType from, PlaneType to) {
    if (from == to)
        return "";
    else if (getLeft(from) == to)
        return "U";
    else if (getRight(from) == to)
        return "U'";
    else
        return "U2";
}

void Solver::rotate(QString s) {
    if (s.isEmpty())
        return;
    result.append(s);
    cube.rotate(s);
}

const Cube &Solver::getCube() const {
    return cube;
}





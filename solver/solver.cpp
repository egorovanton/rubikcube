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
    dropCrossFromTop();
    std::cout << "\n";
}

void Solver::dropCrossFromTop() {

    bool repeat = true;
    while (repeat) {
        std::cout << "W";
        //std::cout << "\n\n" << cube.print().toStdString() << "\n\n";
        repeat = false;
        for (auto currentSide:sides) {
            if (result.isEmpty() || result.last() != "|")
                result << "|";

            //std::cout << planeToString(currentSide).toStdString() << "\n";

            //*************UP*************
            auto tuple = cube.getCubie(UP, currentSide);

            if (std::get<0>(tuple) == DOWN) {
                PlaneType &cubieSide = std::get<1>(tuple);
                rotate(topTwist(currentSide, cubieSide));
                rotate(planeToString(cubieSide) + "2");
                repeat = true;
                continue;
            } else if (std::get<1>(tuple) == DOWN) {
                PlaneType &cubieSide = std::get<0>(tuple);
                if (cubieSide == currentSide) {
                    rotate("U");
                    dropTopRight(getLeft(currentSide));
                    rotate("U'");
                } else if (cubieSide == getLeft(currentSide)) {
                    dropTopLeft(currentSide);
                } else if (cubieSide == getRight(currentSide)) {
                    dropTopRight(currentSide);
                } else if (cubieSide == getBack(currentSide)) {
                    rotate("U");
                    dropTopLeft(getLeft(currentSide));
                    rotate("U'");
                }
                else {
                    std::cout << "FUCKET";
                    throw;
                } //fixme lolwut remove it after testing plz
                repeat = true;
                continue;
            }
            //***********END_UP***********

            //************DOWN************

            tuple = cube.getCubie(DOWN, currentSide);
            if (std::get<0>(tuple) == DOWN) {
                PlaneType &cubieSide = std::get<1>(tuple);
                if (cubieSide != currentSide) {
                    rotate(planeToString(currentSide) + "2");
                    repeat = true;
                    continue;
                }
            } else if (std::get<1>(tuple) == DOWN) {
                PlaneType &cubieSide = std::get<0>(tuple);
                for (auto s : QVector<QString>{planeToString(currentSide) + "'", "U'",
                                               planeToString(getRight(currentSide)), "U"}) {
                    rotate(s);
                }

                repeat = true;
                continue;
            }

            //**********END_DOWN**********

            //************MID*************

            tuple = cube.getCubie(currentSide, getRight(currentSide));
            if (std::get<1>(tuple) == DOWN) {
                if (std::get<0>(tuple) == currentSide)
                    rotate(planeToString(currentSide));
                else
                    rotate(planeToString(currentSide) + "'");
                repeat = true;
                continue;
            } else if (std::get<0>(tuple) == DOWN) {
                rotate("U'");
                rotate(planeToString(getRight(currentSide)));
                rotate("U");
                rotate(planeToString(getRight(currentSide)) + "'");

                if (std::get<1>(tuple) == currentSide)
                    rotate(planeToString(currentSide) + "2");
                repeat = true;
                continue;
            }

            //**********END_MID***********
            //std::cout << "\n";
        }

    }
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




//
// Created by Vetrier on 14/02/2017.
//

#include "solver.h"

#include <iostream>

QStringList Solver::solve() {

    cross();

    //std::cout << "Cross completed\n";
    //std::cout << result.join(" ").toStdString();
    //std::cout << cube.print().toStdString() << "\n";
    bottomCorners();
    //std::cout << "Corners completed\n";
    //std::cout << result.join(" ").toStdString() << "\n";
    //std::cout << cube.print().toStdString() << "\n";
    middleLine();
    //std::cout << "Middle completed\n";

    return result;

}
//***CROSS_SECTION***

void Solver::cross() {
    bool changes = true;
    while (changes) {
        changes = false;
        for (auto c:sides) {
            makeSeparator();
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
    rotate({sCur + "'", L, sCur});
}

void Solver::dropTopRight(PlaneType cur) {
    const QString &R = planeToString(getRight(cur));
    const QString &sCur = planeToString(cur);
    rotate({sCur, R + "'", sCur + "'"});
}

//***END_OF_CROSS_SECTION***

//***BOTTOM_CORNERS_SECTION***

void Solver::bottomCorners() {
    for (auto const f:sides) {
        makeSeparator();
        if (alignBottomCorner(f)) {

            PlaneType const r = getRight(f);
            auto F = planeToString(f);
            auto R = planeToString(getRight(f));

            auto const &type = std::get<0>(cube.getCubie(f, UP, r));

            if (type == f) {
                rotate({R, "U", R + "'"});
            } else if (type == DOWN) {
                rotate({F + "'", "U'", F});
            } else if (type == r) {
                rotate({R, "U2", R + "'", "U'", R, "U", R + "'"});
            } else throw;
        }
    }
}

//placing tight bottom corner above his position
bool Solver::alignBottomCorner(PlaneType f) {
    auto const &r = getRight(f);
    auto tuple = cube.getCubie(f, DOWN, r);
    if (std::get<0>(tuple) == f &&
        std::get<1>(tuple) == DOWN &&
        std::get<2>(tuple) == r)
        return false;
    else {
        //*****DOWN*****
        auto const &b = getBack(f);
        auto const &l = getLeft(f);

        if (cornerMatch(cube.getCubie(f, DOWN, r), f)) {
            auto const &R = planeToString(r);
            rotate({R, "U'", R + "'"});
        } else if (cornerMatch(cube.getCubie(r, DOWN, b), f)) {
            auto const &B = planeToString(b);
            rotate({B, "U", B + "'"});
        } else if (cornerMatch(cube.getCubie(b, DOWN, l), f)) {
            auto const &L = planeToString(l);
            rotate({L, "U2", L + "'"});
        } else if (cornerMatch(cube.getCubie(l, DOWN, f), f)) {
            auto const &L = planeToString(l);
            rotate({L + "'", "U'", L});
        }
        //***END_DOWN***

        //******UP******
        if (cornerMatch(cube.getCubie(f, UP, r), f)) {

        } else if (cornerMatch(cube.getCubie(r, UP, b), f)) {
            rotate("U");
        } else if (cornerMatch(cube.getCubie(b, UP, l), f)) {
            rotate("U2");
        } else if (cornerMatch(cube.getCubie(l, UP, f), f)) {
            rotate("U'");
        } else throw; //wutwtwut
        //****END_UP****
        return true;
    }

}

bool Solver::cornerMatch(std::tuple<PlaneType, PlaneType, PlaneType> t, PlaneType l) {
    auto t1 = std::get<0>(t);
    auto t2 = std::get<1>(t);
    auto t3 = std::get<2>(t);
    auto r = getRight(l);
    return (l == t1 || l == t2 || l == t3)
           && (r == t1 || r == t2 || r == t3)
           && (DOWN == t1 || DOWN == t2 || DOWN == t3);
}

//***END_OF_BOTTOM_CORNERS_SECTION***

//***MIDDLE_SECTION***

void Solver::middleLine() {
    int inPlace = 0;
    for (auto f:sides) {
        PlaneType r = getRight(f);
        auto tuple = cube.getCubie(f, r);
        if (std::get<0>(tuple) == f && std::get<1>(tuple) == r) {
            inPlace++;
        }
    }
    while (inPlace <= 4) {
        makeSeparator();
        if (nextMiddleCubie()) inPlace++;
    }
}
//| F R' F' | L | U' B U B' | U F2 | U2 R U R' | U' L' U' L | U B U2 B' U' B U B'
//| F' U F U R U' R' | U F U' F' U' L' U L | R U' R' U' B' U B | L U' L' U' B' U B | U R U' R' U' F' U F

bool Solver::nextMiddleCubie() {
    for (auto currentFront : sides) {
        auto tuple = cube.getCubie(currentFront, UP);
        auto &f = std::get<0>(tuple);
        auto &u = std::get<1>(tuple);
        if (f != UP && u != UP) {
            if (u == getRight(f)) {
                rotate(topTwist(currentFront, getLeft(f)));
                auto const &F = planeToString(f);
                auto const &R = planeToString(getRight(f));
                rotate({R, "U'", R + "'", "U'", F + "'", "U", F});
            } else if (u == getLeft(f)) {
                rotate(topTwist(currentFront, getRight(f)));
                auto const &F = planeToString(getLeft(f));
                auto const &R = planeToString(f);
                rotate({F + "'", "U", F, "U", R, "U'", R + "'"});
            } else throw;
            return true;
        }
    }
    for (auto currentFront : sides) {
        auto const &currentRight = getRight(currentFront);
        auto tuple = cube.getCubie(currentFront, currentRight);
        auto &f = std::get<0>(tuple);
        auto &r = std::get<1>(tuple);
        if (f != currentFront || r != currentRight) {
            auto const &F = planeToString(currentFront);
            auto const &R = planeToString(getRight(currentFront));
            rotate({R, "U'", R + "'", "U'", F + "'", "U", F});
            return false;
        }
    }

    return true;
}
//***END_OF_MIDDLE_SECTION***

//***COMMON***
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

void Solver::makeSeparator() {
    if (result.isEmpty() || result.last() != "|")
        result << "|";
}

//***END_OF_ALL_ENTIRE_YOUR_EXISTENCES***





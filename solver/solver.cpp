//
// Created by Vetrier on 14/02/2017.
//

#include "solver.h"

#include <iostream>

QStringList Solver::solve() {

    cross();

    //std::cout << "Cross completed\n";
    //std::cout << result.join(" ").toStdString() << "\n";
    //std::cout << cube.print().toStdString() << "\n";
    bottomCorners();
    //std::cout << "Bottom corners completed\n";
    //std::cout << result.join(" ").toStdString() << "\n";
    //std::cout << cube.print().toStdString() << "\n";
    middleLine();
    //std::cout << "Middle completed\n";
    //std::cout << result.join(" ").toStdString() << "\n";
    //std::cout << cube.print().toStdString() << "\n";
    upperCross();
    //std::cout << "Upper cross completed\n";
    //std::cout << result.join(" ").toStdString() << "\n";
    //std::cout << cube.print().toStdString() << "\n";
    upperCorners();
    //std::cout << "Upper corners completed\n";
    //std::cout << result.join(" ").toStdString() << "\n";
    //std::cout << cube.print().toStdString() << "\n";
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

        if (downCornerMatch(cube.getCubie(f, DOWN, r), f)) {
            auto const &R = planeToString(r);
            rotate({R, "U'", R + "'"});
        } else if (downCornerMatch(cube.getCubie(r, DOWN, b), f)) {
            auto const &B = planeToString(b);
            rotate({B, "U", B + "'"});
        } else if (downCornerMatch(cube.getCubie(b, DOWN, l), f)) {
            auto const &L = planeToString(l);
            rotate({L, "U2", L + "'"});
        } else if (downCornerMatch(cube.getCubie(l, DOWN, f), f)) {
            auto const &L = planeToString(l);
            rotate({L + "'", "U'", L});
        }
        //***END_DOWN***

        //******UP******
        if (downCornerMatch(cube.getCubie(f, UP, r), f)) {

        } else if (downCornerMatch(cube.getCubie(r, UP, b), f)) {
            rotate("U");
        } else if (downCornerMatch(cube.getCubie(b, UP, l), f)) {
            rotate("U2");
        } else if (downCornerMatch(cube.getCubie(l, UP, f), f)) {
            rotate("U'");
        } else throw; //wutwtwut
        //****END_UP****
        return true;
    }

}

bool Solver::downCornerMatch(std::tuple<PlaneType, PlaneType, PlaneType> t, PlaneType l) {
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

//***UPPER_CROSS_SECTION***

void Solver::upperOrientation() {
    auto const &f = std::get<1>(cube.getCubie(FRONT, UP));
    auto const &l = std::get<1>(cube.getCubie(LEFT, UP));
    auto const &b = std::get<1>(cube.getCubie(BACK, UP));
    const QStringList &upper1 = {"F", "R", "U", "R'", "U'", "F'", "B", "U", "L", "U'", "L'", "B'"};
    const QStringList &upper2 = {"B", "U", "L", "U'", "L'", "B'"};
    const QStringList &upper3 = {"F", "R", "U", "R'", "U'", "F'"};

    if (f != UP) {
        if (l != UP) {
            if (b != UP) {
                //{1}
                rotate(upper1);
            } else {
                //U {2}
                rotate("U");
                rotate(upper2);
            }
        } else if (b != UP) {
            // {3}
            rotate(upper3);
        } else {
            // U2 {2}
            rotate("U2");
            rotate(upper2);
        }
    } else if (l != UP) {
        if (b != UP) {
            //{2}
            rotate(upper2);
        } else {
            // U {3}
            rotate("U");
            rotate(upper3);
        }
    } else if (b != UP) {
        //U' {2}
        rotate("U'");
        rotate(upper2);
    } else {
        // nothing
    }

}

void Solver::upperOrder() {
    const QStringList &fish = {"R", "U", "R'", "U", "R", "U2", "R'"};
    auto const &f = std::get<0>(cube.getCubie(FRONT, UP));
    auto const &l = std::get<0>(cube.getCubie(LEFT, UP));
    auto const &b = std::get<0>(cube.getCubie(BACK, UP));
    auto const &r = std::get<0>(cube.getCubie(RIGHT, UP));

    if (!(f == FRONT && (l == LEFT || b == BACK || r == RIGHT)
          || (l == LEFT && (b == BACK || r == RIGHT))
          || (b == BACK && r == RIGHT))) {
        rotate("U");
        upperOrder();
        return;
    } else if (f == FRONT && l == LEFT && b == BACK) {
        return;
    } else {
        if (f == FRONT) {
            if (l == LEFT) {
                //U2 {F} U'
                rotate("U2");
                rotate(fish);
                rotate("U'");
            } else if (b == BACK) {
                //U {F} U' {F} U'
                rotate("U");
                rotate(fish);
                rotate("U'");
                rotate(fish);
                rotate("U'");
            } else {
                //U' {F} U2
                rotate("U'");
                rotate(fish);
                rotate("U2");
            }
        } else {
            if (l == LEFT) {
                if (b == BACK) {
                    //U {F}
                    rotate("U");
                    rotate(fish);
                } else {
                    //{F} U' {F}
                    rotate(fish);
                    rotate("U'");
                    rotate(fish);
                }
            } else /*if (b == BACK)*/ {
                //{F} U
                rotate(fish);
                rotate("U");
            }
        }
    }
}

void Solver::upperCross() {
    upperOrientation();
    upperOrder();
}

//***END_OF_UPPER_CROSS_SECTION***

//***UPPER_CORNERS_SECTION***

void Solver::upperCorners() {
    flipUpperCorners();
    //std::cout << "Upper in progress\n";
    //std::cout << result.join(" ").toStdString() << "\n";
    //std::cout << cube.print().toStdString() << "\n";
    placeUpperCorners();
}
void Solver::flipUpperCorners() {
    for (int i = 0; i < 4; i++) {
        auto const &tuple = cube.getCubie(FRONT, UP, RIGHT);
        if (std::get<0>(tuple) == UP) {
            rotate({"R", "F'", "R'", "F", "R", "F'", "R'", "F",});
        } else if (std::get<2>(tuple) == UP) {
            // F' R F R' F' R F R'.
            rotate({"F'", "R", "F", "R'", "F'", "R", "F", "R'"});
        }
        rotate("U");
    }
}

void Solver::placeUpperCorners() {
    auto const &fl = cube.getCubie(FRONT, UP, LEFT);
    auto const &lb = cube.getCubie(LEFT, UP, BACK);
    auto const &br = cube.getCubie(BACK, UP, RIGHT);
    auto const &rf = cube.getCubie(RIGHT, UP, FRONT);
    auto again = false;
    if (std::get<0>(fl) == FRONT && std::get<2>(fl) == LEFT
        && std::get<0>(lb) == LEFT && std::get<2>(lb) == BACK
        && std::get<0>(br) == BACK && std::get<2>(br) == RIGHT
        && std::get<0>(br) == RIGHT && std::get<2>(br) == FRONT) {
        return;
    } else {
        if (uppCornerMatch(lb, BACK)) {
        } else if (uppCornerMatch(fl, LEFT)) {
            result.append("y");
            cube.turnLeft();
        } else if (uppCornerMatch(br, RIGHT)) {
            result.append("y'");
            cube.turnRight();
        } else if (uppCornerMatch(rf, FRONT)) {
            result.append("y2");
            cube.turnHalf();
        } else {
            again = true;
        }
        if (uppCornerMatch(cube.getCubie(RIGHT, UP, BACK), LEFT)) {
            rotate({"F2", "R2", "F", "L", "F'", "R2", "F", "L'", "F"});
        } else {
            rotate({"F'", "L", "F'", "R2", "F", "L'", "F'", "R2", "F2"});
        }
        if (again) placeUpperCorners();
    }
}

bool Solver::uppCornerMatch(std::tuple<PlaneType, PlaneType, PlaneType> t, PlaneType l) {
    auto t1 = std::get<0>(t);
    auto t2 = std::get<1>(t);
    auto t3 = std::get<2>(t);
    auto r = getRight(l);
    return (l == t1 || l == t2 || l == t3)
           && (r == t1 || r == t2 || r == t3);
}
//***END_OF_UPPER_CORNERS_SECTION***




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





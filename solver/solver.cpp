//
// Created by Vetrier on 14/02/2017.
//

#define D(t1, t2) std::make_tuple(t1, t2)
#define TRI(t1, t2, t3) std::make_tuple(t1, t2, t3)

#include "solver.h"

#include <iostream>


Solver::Solver(Cube c) : cube(c) {}

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

QStringList Solver::getPreparedResult() {
    if (result.isEmpty()) solve();
    QStringList preparedResult;

    QString temp = "";
    for (auto s:result) {
        if (s == "|") {
            if (!temp.isEmpty())
                preparedResult << temp;
            preparedResult << s;
            temp = "";
        } else {
            Direction x(temp);
            Direction y(s);
            if (!temp.isEmpty() && !s.isEmpty() && x.getPlane() == y.getPlane()) {
                temp = x.merge(y);
            } else {
                if (!temp.isEmpty())
                    preparedResult << temp;
                temp = s;
            }
        }
    }
    if (!temp.isEmpty())
        preparedResult << temp;

    return preparedResult;
}


QStringList Solver::solveF2L() {
    cross();
    //std::cout << "Cross completed\n";
    //std::cout << result.join(" ").toStdString() << "\n";
    //std::cout << cube.print().toStdString() << "\n";
    for (auto const f:sides) {
        while (F2L());
        alignBottomCorner(f);
        while (F2L());
        if (alignBottomCorner(f)) {
            PlaneType const r = getRight(f);
            auto Fr = planeToString(f);
            auto Ri = planeToString(getRight(f));

            auto const &type = std::get<0>(cube.getCubie(f, U, r));

            if (type == f) {
                rotate({Ri, "U", Ri + "'"});
            } else if (type == DOWN) {
                rotate({Fr + "'", "U'", Fr});
            } else if (type == r) {
                rotate({Ri, "U2", Ri + "'", "U'", Ri, "U", Ri + "'"});
            } else throw;
        }
        while (F2L());
    }

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


QStringList Solver::getPreparedResultF2L() {
    if (result.isEmpty()) solveF2L();
    QStringList preparedResult;

    QString temp = "";
    for (auto s:result) {
        if (s == "|") {
            if (!temp.isEmpty())
                preparedResult << temp;
            preparedResult << s;
            temp = "";
        } else {
            Direction x(temp);
            Direction y(s);
            if (!temp.isEmpty() && !s.isEmpty() && x.getPlane() == y.getPlane()) {
                temp = x.merge(y);
            } else {
                if (!temp.isEmpty())
                    preparedResult << temp;
                temp = s;
            }
        }
    }
    if (!temp.isEmpty())
        preparedResult << temp;

    return preparedResult;
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
    auto tuple = cube.getCubie(U, currentSide);

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
    const QString &Le = planeToString(getLeft(cur));
    const QString &sCur = planeToString(cur);
    rotate({sCur + "'", Le, sCur});
}

void Solver::dropTopRight(PlaneType cur) {
    const QString &Ri = planeToString(getRight(cur));
    const QString &sCur = planeToString(cur);
    rotate({sCur, Ri + "'", sCur + "'"});
}

//***END_OF_CROSS_SECTION***

//***F2L_SECTION***

//changes bool
//todo move consts FCN OUT OF HEAR
bool Solver::F2L() {
    for (int frontSide = 0; frontSide < 4; frontSide++) {
        for (int uTurns = 0; uTurns < 4; ++uTurns) {

            static auto const pos1 = TRI(F, DOWN, R);
            static auto const pos2 = D(F, R);

            Mask rightPos;
            rightPos.setCubie(pos1, pos1);
            rightPos.setCubie(pos2, pos2);
            if (cube.fitsMask(rightPos)) continue;

            for (int cornerInd = 0; cornerInd < corners.length(); cornerInd++) {
                Mask corner;
                corner.setCubie(corners[cornerInd], pos1);
                if (cube.fitsMask(corner)) {
                    for (int j = 0; j < middleD[cornerInd].length(); j++) {
                        Mask f2l;
                        f2l.setCubie(middleD[cornerInd][j], pos2);
                        if (cube.fitsMask(f2l)) {
                            makeSeparator();
                            rotate(rot[cornerInd][j]);
                            return true;
                        }
                    }
                }
            }
            rotate("U");
        }
        rotate("y");
    }
    return false;
}

void Solver::bottomCorners() {
    for (auto const f:sides) {
        makeSeparator();
        if (alignBottomCorner(f)) {

            PlaneType const r = getRight(f);
            auto Fr = planeToString(f);
            auto Ri = planeToString(getRight(f));

            auto const &type = std::get<0>(cube.getCubie(f, U, r));

            if (type == f) {
                rotate({Ri, "U", Ri + "'"});
            } else if (type == DOWN) {
                rotate({Fr + "'", "U'", Fr});
            } else if (type == r) {
                rotate({Ri, "U2", Ri + "'", "U'", Ri, "U", Ri + "'"});
            } else throw;
        }
    }
}

//placing right bottom corner above his position
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
            auto const &Ri = planeToString(r);
            rotate({Ri, "U'", Ri + "'"});
        } else if (downCornerMatch(cube.getCubie(r, DOWN, b), f)) {
            auto const &Ba = planeToString(b);
            rotate({Ba, "U", Ba + "'"});
        } else if (downCornerMatch(cube.getCubie(b, DOWN, l), f)) {
            auto const &Le = planeToString(l);
            rotate({Le, "U2", Le + "'"});
        } else if (downCornerMatch(cube.getCubie(l, DOWN, f), f)) {
            auto const &Le = planeToString(l);
            rotate({Le + "'", "U'", Le});
        }
        //***END_DOWN***

        //******U******
        if (downCornerMatch(cube.getCubie(f, U, r), f)) {

        } else if (downCornerMatch(cube.getCubie(r, U, b), f)) {
            rotate("U");
        } else if (downCornerMatch(cube.getCubie(b, U, l), f)) {
            rotate("U2");
        } else if (downCornerMatch(cube.getCubie(l, U, f), f)) {
            rotate("U'");
        } else throw; //wutwtwut
        //****END_U****
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
        auto tuple = cube.getCubie(currentFront, U);
        auto &f = std::get<0>(tuple);
        auto &u = std::get<1>(tuple);
        if (f != U && u != U) {
            if (u == getRight(f)) {
                rotate(topTwist(currentFront, getLeft(f)));
                auto const &Fi = planeToString(f);
                auto const &Ri = planeToString(getRight(f));
                rotate({Ri, "U'", Ri + "'", "U'", Fi + "'", "U", Fi});
            } else if (u == getLeft(f)) {
                rotate(topTwist(currentFront, getRight(f)));
                auto const &Fr = planeToString(getLeft(f));
                auto const &Ri = planeToString(f);
                rotate({Fr + "'", "U", Fr, "U", Ri, "U'", Ri + "'"});
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
            auto const &Fr = planeToString(currentFront);
            auto const &Ri = planeToString(getRight(currentFront));
            rotate({Ri, "U'", Ri + "'", "U'", Fr + "'", "U", Fr});
            return false;
        }
    }

    return true;
}
//***END_OF_F2L_SECTION***

//***UPER_CROSS_SECTION***

void Solver::upperOrientation() {
    auto const &f = std::get<1>(cube.getCubie(F, U));
    auto const &l = std::get<1>(cube.getCubie(L, U));
    auto const &b = std::get<1>(cube.getCubie(B, U));
    static const QStringList &upper1 = {"F", "R", "U", "R'", "U'", "F'", "B", "U", "L", "U'", "L'", "B'"};
    static const QStringList &upper2 = {"B", "U", "L", "U'", "L'", "B'"};
    static const QStringList &upper3 = {"F", "R", "U", "R'", "U'", "F'"};

    if (f != U) {
        if (l != U) {
            if (b != U) {
                //{1}
                rotate(upper1);
            } else {
                //U {2}
                rotate("U");
                rotate(upper2);
            }
        } else if (b != U) {
            // {3}
            rotate(upper3);
        } else {
            // U2 {2}
            rotate("U2");
            rotate(upper2);
        }
    } else if (l != U) {
        if (b != U) {
            //{2}
            rotate(upper2);
        } else {
            // U {3}
            rotate("U");
            rotate(upper3);
        }
    } else if (b != U) {
        //U' {2}
        rotate("U'");
        rotate(upper2);
    } else {
        // nothing
    }

}

void Solver::upperOrder() {
    static const QStringList &fish = {"R", "U", "R'", "U", "R", "U2", "R'"};
    auto const &f = std::get<0>(cube.getCubie(F, U));
    auto const &l = std::get<0>(cube.getCubie(L, U));
    auto const &b = std::get<0>(cube.getCubie(B, U));
    auto const &r = std::get<0>(cube.getCubie(R, U));

    if (!(f == F && (l == L || b == B || r == R)
          || (l == L && (b == B || r == R))
          || (b == B && r == R))) {
        rotate("U");
        upperOrder();
        return;
    } else if (f == F && l == L && b == B) {
        return;
    } else {
        if (f == F) {
            if (l == L) {
                //U2 {F} U'
                rotate("U2");
                rotate(fish);
                rotate("U'");
            } else if (b == B) {
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
            if (l == L) {
                if (b == B) {
                    //U {F}
                    rotate("U");
                    rotate(fish);
                } else {
                    //{F} U' {F}
                    rotate(fish);
                    rotate("U'");
                    rotate(fish);
                }
            } else /*if (b == B)*/ {
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

//***END_OF_UPER_CROSS_SECTION***

//***UPER_CORNERS_SECTION***

void Solver::upperCorners() {
    flipUpperCorners();
    //std::cout << "Upper in progress\n";
    //std::cout << result.join(" ").toStdString() << "\n";
    //std::cout << cube.print().toStdString() << "\n";
    placeUpperCorners();
}

void Solver::flipUpperCorners() {
    for (int i = 0; i < 4; i++) {
        auto const &tuple = cube.getCubie(F, U, R);
        if (std::get<0>(tuple) == U) {
            rotate({"R", "F'", "R'", "F", "R", "F'", "R'", "F",});
        } else if (std::get<2>(tuple) == U) {
            // F' R F R' F' R F R'.
            rotate({"F'", "R", "F", "R'", "F'", "R", "F", "R'"});
        }
        rotate("U");
    }
}

void Solver::placeUpperCorners() {
    auto const &fl = cube.getCubie(F, U, L);
    auto const &lb = cube.getCubie(L, U, B);
    auto const &br = cube.getCubie(B, U, R);
    auto const &rf = cube.getCubie(R, U, F);
    auto again = false;
    //std::cout << printTuple(fl) << std::endl;
    //std::cout << printTuple(lb) << std::endl;
    //std::cout << printTuple(br) << std::endl;
    //std::cout << printTuple(rf) << std::endl;
    if (std::get<0>(fl) == F && std::get<2>(fl) == L
        && std::get<0>(lb) == L && std::get<2>(lb) == B
        && std::get<0>(br) == B && std::get<2>(br) == R
        && std::get<0>(rf) == R && std::get<2>(rf) == F) {
        return;
    } else {
        if (uppCornerMatch(lb, B)) {
        } else if (uppCornerMatch(fl, L)) {
            result.append("y");
            cube.turnLeft();
        } else if (uppCornerMatch(br, R)) {
            result.append("y'");
            cube.turnRight();
        } else if (uppCornerMatch(rf, F)) {
            result.append("y2");
            cube.turnHalf();
        } else {
            again = true;
        }
        if (uppCornerMatch(cube.getCubie(R, U, B), L)) {
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
//***END_OF_UPER_CORNERS_SECTION***




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




/* kinda backup
         static const QVector<Triple> corners = {
                {U, F, R}, {F, R, U}, {R, U, F},
                {B, U, R}, {F, U, L}, {F, U, B},
                {R, F, DOWN}, {DOWN, R, F}, {F, DOWN, R}
        };

        for(int cornerInd = 0; cornerInd < corners.length(); cornerInd++){
            Mask corner;
            static auto const pos1 = T(F, DOWN, R);
            corner.setCubie(corners[cornerInd], pos1);
            if (cube.fitsMask(corner)){
                static const QVector<QVector<Duo>> middleD = {{
                        {F, R}, {R, F}, {U, R}, {L, U}, {U, B},
                        {U, L}, {B, U}, {R, U}, {F, U}, {U, F}
                    }, {
                        {F, R}, {R, F}, {F, U}, {U, B}, {L, U},
                        {B, U}, {U, L}, {U, F}, {U, R}, {R, U}
                    }, {
                        {F, R}, {R, F}, {F, U},
                        {U, F}, {R, U}, {U, F}
                    }, {F, U}, {U, R}, {{F, U}, {U, R}}, {
                        {F, R}, {R, F}, {F, U}, {U, R}
                    }, {
                        {F, R}, {R, F}, {F, U}, {U, R}
                    }, {
                        {F, U}, {U, R}, {R, F}
                    }
                };
                static auto const pos2 = D(F, R);
                static const QVector<QVector<QStringList>> rot = {{
                        S("U' R U' R' U2 R U' R'"), S("U2 R U R' y U' L' U L"),
                        S("U R U' R'"), S("F' U' F"), S("U' R U R' U2 R U' R'"),
                        S("U' R U2 R' U2 R U' R'"), S("F R U R' U' F' R U' R'"),
                        S("y' R U2 R2 U' R2 U' R'"), S("y' U R' U R U' R' U' R"),
                        S("R U R' U2 R U' R' U R U' R'")
                    }, {
                        S("U' R U2' R' U R U R'"), S("U F' U' F U' R U R'"),
                        S("y U' L' U L"), S("R U R'"), S("y' U R' U' R U R' U2 R"),
                        S("y' U R' U2 R U R' U2 R"), S("U' R U R' U R U R'"),
                        S("R U' R' U R U' R' U2 R U' R'"), S("U' R U' R' U R U R'")
                        S("R U' R' y' U2 R' U' R")
                    }, {
                        S("U R U' R' U R U' R' U R U' R'"), S("R U' R' U y' R' U R"),
                        S("y' R' U2 R U R' U' R"), S("R U2 R' U' R U R'"),
                        S("y U' L' U L U L' U L U' L' U L"), S("R U' R' U R U2 R' U R U R'")
                    }, {S("y' R' U2 R U' R' U R")}, {S("R U2 R' U R U' R'")},{
                        S("R U R' F' U' F"), S("R U R' U R U' R'")
                    }, {
                        S("R U' R' U' R U R' U2 R U' R'"), S("R F U R U' R' F' U' R'"),
                        S("y L' U' L U L' U' L"), S("R U' R' U R U' R'")
                    }, {
                        S("R U2 R U R' U R U2 R2'"), S("y F R U2 R' F' L' U' L"),
                        S("y L' U L U' L' U L"), S("R U R' U' R U R'")
                    }, {
                        S("U R U' R' F R' F' R"), S("R' F' R U R U' R' F"), S("R U' R' U y' R' U2 R U2' R' U R")
                    }
                };
*/
//
// Created by Vetrier on 14/02/2017.
//

#ifndef RUBIKCUBE_SOLVER_H
#define RUBIKCUBE_SOLVER_H
#define S(t) ((QString) t).split(" ")
#define F FRONT
#define U UP
#define B BACK
#define L LEFT
#define R RIGHT


#include "../twister/cube.h"
#include "../twister/mask.h"

class Solver {
public:
    Solver(Cube c);

    QStringList solve();

    QStringList solveF2L();

    const Cube &getCube() const;

    QStringList getPreparedResult() {
        if (result.isEmpty()) solve();
        QStringList preparedResult;
        return prep();
    }

    QStringList getPreparedResultF2L() {
        if (result.isEmpty()) solveF2L();
        return prep();
    }

private:
    QStringList prep();
    Cube cube;
    QStringList result;
    const PlaneType sides[4] = {FRONT, LEFT, BACK, RIGHT};

    void cross();

    bool upPlane(PlaneType currentSide);

    bool downPlane(PlaneType currentSide);

    bool midPlane(PlaneType currentSide);

    void dropTopLeft(PlaneType cur);

    void dropTopRight(PlaneType cur);

    //Fridric
    bool F2L();

    void bottomCorners();

    bool alignBottomCorner(PlaneType f);

    bool downCornerMatch(std::tuple<PlaneType, PlaneType, PlaneType> t, PlaneType l);

    void middleLine();

    bool nextMiddleCubie();

    void upperOrientation();

    void upperOrder();

    void upperCross();

    void rotate(QString s);

    void rotate(QStringList q) {
        for (auto s:q) rotate(s);
    }

    void makeSeparator();

    QString topTwist(PlaneType from, PlaneType to);

    void flipUpperCorners();

    void placeUpperCorners();

    bool uppCornerMatch(std::tuple<PlaneType, PlaneType, PlaneType> t, PlaneType l);

    void upperCorners();

    const QVector<QVector<Duo>> middleD = {
            {{F, R}, {R, F}, {U, R}, {L, U}, {U, B}, {U, L}, {B, U}, {R, U}, {F, U}, {U, F}},
            {{F, R}, {R, F}, {F, U}, {U, B}, {L, U}, {B, U}, {U, L}, {U, F}, {U, R}, {R, U}},
            {{F, R}, {R, F}, {F, U}, {U, F}, {R, U}, {U, F}},
            {{F, U}},
            {{U, R}},
            {{F, U}, {U, R}},
            {{F, R}, {R, F}, {F, U}, {U, R}},
            {{F, R}, {R, F}, {F, U}, {U, R}},
            {{F, U}, {U, R}, {R, F}}
    };
    const QVector<QVector<QStringList>> rot = {
            {S("U' R U' R' U2 R U' R'"),  S("U2 R U R' y U' L' U L"), S("U R U' R'"),
             S("F' U' F"), S("U' R U R' U2 R U' R'"),
             S("U' R U2 R' U2 R U' R'"),  S("F R U R' U' F' R U' R'"), S("y' R U2 R2 U' R2 U' R'"),
             S("y' U R' U R U' R' U' R"),  S("R U R' U2 R U' R' U R U' R'")},

             {S("U' R U2' R' U R U R'"), S("U F' U' F U' R U R'"),
             S("y U' L' U L"),    S("R U R'"),  S("y' U R' U' R U R' U2 R"),
             S("y' U R' U2 R U R' U2 R"), S("U' R U R' U R U R'"),
             S("R U' R' U R U' R' U2 R U' R'"), S("U' R U' R' U R U R'"), S("R U' R' y' U2 R' U' R")},

             {S("U R U' R' U R U' R' U R U' R'"), S("R U' R' U y' R' U R"),
              S("y' R' U2 R U R' U' R"), S("R U2 R' U' R U R'"),
              S("y U' L' U L U L' U L U' L' U L"), S("R U' R' U R U2 R' U R U R'")},

             {S("y' R' U2 R U' R' U R")},

             {S("R U2 R' U R U' R'")},

             {S("R U R' F' U' F"),  S("R U R' U R U' R'")},

             {S("R U' R' U' R U R' U2 R U' R'"),  S("R F U R U' R' F' U' R'"),
              S("y L' U' L U L' U' L"),  S("R U' R' U R U' R'")},

             {S("R U2 R U R' U R U2 R2'"), S("y F R U2 R' F' L' U' L"),
              S("y L' U L U' L' U L"),   S("R U R' U' R U R'")},

             {S("U R U' R' F R' F' R"),   S("R' F' R U R U' R' F"),  S("R U' R' U y' R' U2 R U2' R' U R")}
            };
    const QVector<Triple> corners = {
            {U,    F, R},
            {F,    R, U},
            {R,    U, F},
            {B,    U, R},
            {F,    U, L},
            {L,    U, B},
            {R,    F, DOWN},
            {DOWN, R, F},
            {F, DOWN, R}
    };
};


#endif //RUBIKCUBE_SOLVER_H

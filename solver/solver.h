//
// Created by Vetrier on 14/02/2017.
//

#ifndef RUBIKCUBE_SOLVER_H
#define RUBIKCUBE_SOLVER_H


#include "../twister/cube.h"

enum SideFlag {
    U = 1,
    MID = 2,
    D = 3
};

class Solver {
public:
    Solver(Cube c): cube(c) {};
    QStringList solve();

private:
    Cube cube;
public:
    const Cube &getCube() const;

private:
    QStringList result;
    const PlaneType sides[4] = {FRONT, LEFT, BACK, RIGHT};
    void rotate(QString s);

    void cross();

    void dropCrossFromTop();
    void dropTopLeft(PlaneType cur);
    void dropTopRight(PlaneType cur);

    QString topTwist(PlaneType from, PlaneType to);
};


#endif //RUBIKCUBE_SOLVER_H

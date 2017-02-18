//
// Created by Vetrier on 14/02/2017.
//

#ifndef RUBIKCUBE_SOLVER_H
#define RUBIKCUBE_SOLVER_H


#include "../twister/cube.h"

class Solver {
public:
    Solver(Cube c): cube(c) {};
    QStringList solve();
    QStringList getPreparedResult();

private:
    Cube cube;
public:
    const Cube &getCube() const;

private:
    QStringList result;
    const PlaneType sides[4] = {FRONT, LEFT, BACK, RIGHT};

    void cross();
    bool upPlane(PlaneType currentSide);
    bool downPlane(PlaneType currentSide);
    bool midPlane(PlaneType currentSide);
    void dropTopLeft(PlaneType cur);
    void dropTopRight(PlaneType cur);

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
        for(auto s:q) rotate(s);
    }
    void makeSeparator();
    QString topTwist(PlaneType from, PlaneType to);

    void flipUpperCorners();

    void placeUpperCorners();

    bool uppCornerMatch(std::tuple<PlaneType, PlaneType, PlaneType> t, PlaneType l);

    void upperCorners();

};


#endif //RUBIKCUBE_SOLVER_H
